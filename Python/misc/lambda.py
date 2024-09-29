#!/home/ubuntu/wspace-2/anaconda2/bin/python

def main():
    x = [1, 2, 3, 4, 5]
    y = map(lambda a: a*a, x)
    z = map(lambda a,b: a+b, x, y)

    print x
    print y
    print z

if __name__ == '__main__':
    main()
