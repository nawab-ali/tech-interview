#!/home/ubuntu/wspace-2/anaconda2/bin/python

import numpy as np

def reshape_array():
    a = np.random.random((3,4))

    print a
    print a.ravel()
    print a.T
    print a.T.shape
    print a.reshape(6,2)
    print a.reshape(6,-1)

def stack_arrays():
    a = np.floor(10*np.random.random((2,2)))
    b = np.floor(10*np.random.random((2,2)))

    print a
    print b
    print np.vstack((a,b))
    print np.hstack((a,b))

def main():
    #reshape_array()
    stack_arrays()

if __name__ == '__main__':
    main()
