#!/home/ubuntu/wspace-2/anaconda2/bin/python

import numpy as np

def broadcast_add():
    a = np.arange(20).reshape((5,4))
    print a
    print a+5

def main():
    broadcast_add()

if __name__ == '__main__':
    main()
