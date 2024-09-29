#!/home/ubuntu/wspace-2/anaconda2/bin/python

""" Count number of lines, words, and characters in text file. """

import sys

def main():
    num_words = 0
    num_chars = 0

    if len(sys.argv) < 3:
        print 'Usage:', sys.argv[0], '<input_file>', '<output_file>'
        exit(1)
    else:
        input_file_name = sys.argv[1]
        output_file_name = sys.argv[2]

    with open(input_file_name, 'r') as input_file_handle:
        lines = [line for line in input_file_handle]

    for line in lines:
        num_words += count_words(line)
        num_chars += count_characters(line)

    with open(output_file_name, 'w') as output_file_handle:
        output_file_handle.write(str(len(lines)) + ' ' + str(num_words) + ' ' + str(num_chars))

    print len(lines), num_words, num_chars

def count_words(line):
    return len(line.split())

def count_characters(line):
    return len(line)

if __name__ == '__main__':
    main()
