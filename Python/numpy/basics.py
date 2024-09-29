#!/home/ubuntu/wspace-2/anaconda2/bin/python

import numpy as np

def print_array_attributes():
    a = np.arange(15).reshape(3,5)
    print a
    print a.shape, a.ndim, a.size, a.itemsize, type(a)

def create_array():
    a = np.array([1,2,3], dtype=np.int32)
    b = np.array([[1,2,3],[5,6,7]], dtype=np.float16)
    print a
    print a.shape, a.ndim, a.size, a.itemsize, type(a), a.dtype
    print b
    print b.shape, b.ndim, b.size, b.itemsize, type(b), b.dtype

    c = np.zeros((3,4), dtype=np.int16)
    print c

    d = np.ones((4,5), dtype=np.float16)
    print d

def math_operations():
    a = np.array([5,6,7,8])
    b = np.arange(4)
    c = np.arange(12).reshape(3,4)
    d = np.arange(20).reshape(4,5)
    e = np.random.random((3,4))

    print a
    print b
    print a+b
    print a-b
    print a*b
    print b/a
    print c.dot(d)
    print e
    print e.sum()
    print e.min()
    print e.max()
    print e.sum(axis=0)
    print e.min(axis=1)
    print a
    print np.exp(a)
    print np.sqrt(a)
    print a[::-1]
    print a[0:3:2]
    print c[2,3]

    print e
    for element in e.flat:
        print element

def main():
    #print_array_attributes()
    #create_array()
    math_operations()

if __name__ == '__main__':
    main()
