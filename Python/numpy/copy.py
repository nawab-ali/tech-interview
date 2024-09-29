#!/home/ubuntu/wspace-2/anaconda2/bin/python

import numpy as np

def shallow_copy():
    a = np.array([1,2,3,4])
    b = a
    print a
    print id(a)
    print id(b)

def deep_copy():
    a = np.array([1,2,3,4])
    b = a.copy()
    print a
    print id(a)
    print id(b)

def main():
    #shallow_copy()
    deep_copy()

if __name__ == '__main__':
    main()
