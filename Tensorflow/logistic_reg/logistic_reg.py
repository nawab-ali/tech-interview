#!/home/ubuntu/anaconda3/envs/tensorflow_p36/bin/python
## Logistic Regression model for MNIST

import os
import sys
import time
import utils
import numpy as np
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

# Download the MNIST data
def logistic_reg_mnist_download():
    mnist_folder = 'data/mnist'
    utils.download_mnist(mnist_folder)
    train, val, test = utils.read_mnist(mnist_folder, flatten=True)

    # We ignore the validation test data in this problem
    return train, test

# Create train, test datasets
def logistic_reg_create_datasets(data, batch):
    dataset = tf.data.Dataset.from_tensor_slices(data)
    return dataset.batch(batch)

# Train the model
def logistic_reg_train(sess, n_epochs, train_init, optimizer, loss):
    start_time = time.time()

    # Train the model for n epochs
    for i in range(n_epochs):
        sess.run(train_init)
        total_loss = 0
        n_batches = 0

        try:
            while True:
                _, l = sess.run([optimizer, loss])
                total_loss += l
                n_batches += 1
        except tf.errors.OutOfRangeError:
            pass
        print('Average loss epoch {0}: {1}'.format(i, total_loss/n_batches))
    print('TTT: {0}s'.format(time.time() - start_time))

# Test the model
def logistic_reg_test(sess, test_init, accuracy, n_test):
    sess.run(test_init)
    total_correct_preds = 0
    try:
        while True:
            accuracy_batch = sess.run(accuracy)
            total_correct_preds += accuracy_batch
    except tf.errors.OutOfRangeError:
        pass
    print('Accuracy: {0}'.format(total_correct_preds/n_test))

# Main function
def main():
    # Model training parameters
    n_epochs = 30
    n_test = 10000
    batch_size = 32
    learning_rate = 0.01

    # Download the MNIST data
    train, test = logistic_reg_mnist_download()

    # Create datasets
    train_data = logistic_reg_create_datasets(train, batch_size)
    test_data = logistic_reg_create_datasets(test, batch_size)

    # Create an iterator and initialize it with different datasets
    iterator = tf.data.Iterator.from_structure(train_data.output_types, train_data.output_shapes)
    img, label = iterator.get_next()
    train_init = iterator.make_initializer(train_data)
    test_init = iterator.make_initializer(test_data)

    # Create weights and bias
    # w is initialized to random variables with mean of 0, stddev of 0.01
    # b is initialized to 0
    # Shape of w depends on the dimension of X and Y so that Y = tf.matmul(X, w)
    # Shape of b depends on Y
    w = tf.get_variable(name='weights', shape=(784, 10), dtype=tf.float32,
                        initializer=tf.random_normal_initializer(0, 0.01))
    b = tf.get_variable(name='bias', shape=(1, 10), dtype=tf.float32,
                        initializer=tf.zeros_initializer())

    # Build the logistic regression model
    logits = tf.add(tf.matmul(img, w), b)

    # Define the loss function
    entropy = tf.nn.softmax_cross_entropy_with_logits(logits=logits, labels=label, name='entropy')
    loss = tf.reduce_mean(entropy, name='loss')

    # Define training
    optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss)

    # Calculate accuracy with test data set
    preds = tf.nn.softmax(logits)
    correct_preds = tf.equal(tf.argmax(preds, 1), tf.argmax(label, 1))
    accuracy = tf.reduce_sum(tf.cast(correct_preds, tf.float32))

    with tf.Session(config=tf.ConfigProto(log_device_placement=True)) as sess:
        sess.run(tf.global_variables_initializer())

        # Train the model
        logistic_reg_train(sess, n_epochs, train_init, optimizer, loss)

        # Test the model
        logistic_reg_test(sess, test_init, accuracy, n_test)

if __name__ == '__main__':
    sys.exit(main())
