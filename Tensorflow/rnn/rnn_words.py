#!/home/ubuntu/anaconda3/envs/tensorflow_p36/bin/python
'''
A Recurrent Neural Network (LSTM) example using TensorFlow.
Next word prediction after n_input words learned from text file.
A story is automatically generated if the predicted word is fed back as input.
'''

from __future__ import division
from __future__ import print_function

import time
import random
import collections
import numpy as np
import tensorflow as tf
from tensorflow.contrib import rnn

def elapsed_time(sec):
    ''' Return time in appropriate unit'''

    if sec < 60:
        return(str(sec) + ' s')
    elif sec < (60*60):
        return(str(sec/60) + ' min')
    else:
        return(str(sec/(60*60)) + ' hr')

def read_data(fname):
    ''' Read data from file '''

    with open(fname) as f:
        content = f.readlines()
    content = [x.strip() for x in content]
    content = [word for i in range(len(content)) for word in content[i].split()]
    content = np.array(content)
    return content

def build_dataset(words):
    ''' Build a training dataset '''

    count = collections.Counter(words).most_common()
    dictionary = dict()

    for word, _ in count:
        dictionary[word] = len(dictionary)
    reverse_dictionary = dict(zip(dictionary.values(), dictionary.keys()))

    return dictionary, reverse_dictionary

def RNN(x, weights, biases, n_input, n_hidden):
    ''' Implement the RNN '''

    # Reshape the input
    x = tf.reshape(x, [-1, n_input])

    # Generate a n_input sequence of inputs
    # e.g. [had] [a] [general] -> [20] [6] [33]
    x = tf.split(x, n_input, 1)

    # 2-layer LSTM, each layer has n_hidden units
    rnn_cell = rnn.MultiRNNCell([rnn.BasicLSTMCell(n_hidden), rnn.BasicLSTMCell(n_hidden)])

    # Generate prediction
    outputs, states = rnn.static_rnn(rnn_cell, x, dtype=tf.float32)

    # There are n_input outputs but we only want the last output
    return tf.matmul(outputs[-1], weights['out']) + biases['out']

def main():
    ''' Main function '''

    # Training parameters
    n_input = 3
    n_hidden = 512
    display_step = 1000
    learning_rate = 0.001
    training_iters = 50000

    # Start the timer
    start_time = time.time()

    # Text file containing words for training
    training_file = './training.txt'

    # Build the training dataset
    training_data = read_data(training_file)
    dictionary, reverse_dictionary = build_dataset(training_data)
    vocab_size = len(dictionary)

    # TF input
    x = tf.placeholder('float', [None, n_input, 1])
    y = tf.placeholder('float', [None, vocab_size])

    # RNN output nodes weights and biases
    weights = {'out': tf.Variable(tf.random_normal([n_hidden, vocab_size]))}
    biases = {'out': tf.Variable(tf.random_normal([vocab_size]))}

    pred = RNN(x, weights, biases, n_input, n_hidden)

    # Loss and optimizer
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=pred, labels=y))
    optimizer = tf.train.RMSPropOptimizer(learning_rate=learning_rate).minimize(cost)

    # Model evaluation
    correct_pred = tf.equal(tf.argmax(pred, 1), tf.argmax(y, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))

    # Initialize the global variables
    init = tf.global_variables_initializer()

    # Launch the TF graph
    with tf.Session() as sess:
        sess.run(init)
        step = 0
        offset = random.randint(0, n_input+1)
        end_offset = n_input + 1
        acc_total = 0
        loss_total = 0

        while (step < training_iters):
            # Generate a minibatch. Add some randomness on the selection process.
            if offset > (len(training_data)-end_offset):
                offset = random.randint(0, n_input+1)

            symbols_in_keys = [ [dictionary[str(training_data[i])]] for i in range(offset, offset+n_input) ]
            symbols_in_keys = np.reshape(np.array(symbols_in_keys), [-1, n_input, 1])

            symbols_out_onehot = np.zeros([vocab_size], dtype=float)
            symbols_out_onehot[dictionary[str(training_data[offset+n_input])]] = 1.0
            symbols_out_onehot = np.reshape(symbols_out_onehot, [1, -1])

            _, acc, loss, onehot_pred = sess.run([optimizer, accuracy, cost, pred], feed_dict={x:
                                        symbols_in_keys, y: symbols_out_onehot})

            loss_total += loss
            acc_total += acc

            if (step+1) % display_step == 0:
                print('Iter: ' + str(step+1) + ', Avg. loss: ' + \
                      '{:.6f}'.format(loss_total/display_step) + ', Avg. accuracy: ' + \
                      '{:.2f}%'.format(100*acc_total/display_step))
                acc_total = 0
                loss_total = 0

                symbols_in = [training_data[i] for i in range(offset, offset+n_input)]
                symbols_out = training_data[offset+n_input]
                symbols_out_pred = reverse_dictionary[int(tf.argmax(onehot_pred, 1).eval())]
                print('%s - [%s] vs [%s]' % (symbols_in, symbols_out, symbols_out_pred))

            step += 1
            offset += (n_input+1)

        print('Training complete')
        print('Elapsed Time: ', elapsed_time(time.time()-start_time))

        sentence = 'had a general'
        words = sentence.split(' ')
        try:
            symbols_in_keys = [dictionary[str(words[i])] for i in range(len(words))]
            for i in range(32):
                keys = np.reshape(np.array(symbols_in_keys), [-1, n_input, 1])
                onehot_pred = sess.run(pred, feed_dict={x: keys})
                onehot_pred_index = int(tf.argmax(onehot_pred, 1).eval())
                sentence = '%s %s' % (sentence, reverse_dictionary[onehot_pred_index])
                symbols_in_keys = symbols_in_keys[1:]
                symbols_in_keys.append(onehot_pred_index)
            print(sentence)
        except:
            print('Word not in dictionary')

if __name__ == '__main__':
    main()
