#!/home/ubuntu/wspace-2/anaconda2/bin/python

from operator import itemgetter

def main():
    inventory = [('apple', 3), ('banana', 2), ('pear', 5), ('orange', 1)]
    inventory.sort(key=itemgetter(1), reverse=True)

    print inventory

if __name__ == '__main__':
    main()
