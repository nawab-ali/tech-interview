#!/home/ubuntu/wspace-2/anaconda2/bin/python

def main():
    stack = []

    for i in range(10):
        stack.append(i)

    while len(stack) > 0:
        print stack.pop()

if __name__ == '__main__':
    main()
