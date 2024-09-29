""" Wordcount -- Count the number of lines, words, characters in text. """

import urllib.request

def tokenize(string):
    if string is None:
        return None

    return [token.strip() for token in string.split()]

def main():
    url = 'https://pastebin.com/raw/Qgfnuhe4'
    data = str(urllib.request.urlopen(url).read())

    lines = data.splitlines()
    words = tokenize(data)

    print(len(lines), len(words), len(data))

if __name__ == '__main__':
    main()