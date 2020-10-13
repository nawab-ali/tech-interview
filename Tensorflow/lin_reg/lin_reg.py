#!/home/ubuntu/anaconda3/envs/tensorflow_p36/bin/python
## Predicting life expectancy from birth rate using Linear Regression

import os
import sys
import time
import utils
import numpy as np
import tensorflow as tf

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
DATA_FILE = 'birth_life_2010.txt'

def main():
    # Read in data from the .txt file
    data, n_samples = utils.read_birth_life_data(DATA_FILE)

    X = tf.placeholder(tf.float32, shape=(), name='X')
    Y = tf.placeholder(tf.float32, shape=(), name='Y')

    w = tf.get_variable('weights', initializer=tf.constant(0.))
    b = tf.get_variable('bias', initializer=tf.constant(0.))

    # Build linear regression model
    Y_predicted = tf.add(tf.multiply(w, X), b)

    loss = tf.square(tf.subtract(Y_predicted, Y))

    # Use gradient descent with learning rate of 0.001 to minimize loss
    optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.001).minimize(loss)

    start = time.time()

    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())

        # Train the model for 100 epochs
        for i in range(100):
            for x, y in data:
                sess.run(optimizer, feed_dict={X: x, Y: y})

        w_out, b_out = sess.run([w, b])
        print('w: %f b: %f' % (w_out, b_out))

    print('Time: %fs' % (time.time() - start))

if __name__ == '__main__':
    sys.exit(main())
