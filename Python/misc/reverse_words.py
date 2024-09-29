# Reverse the words in a string

# Input: s = 'geeks quiz practice code'
# Output: s = 'code practice quiz geeks'

# Input: s = 'getting good at coding needs a lot of practice'
# Output: s = 'practice of lot a needs coding at good getting'

def reverse_words_in_string(string):
    if string is None:
        return None

    words = [word.strip() for word in string.split()]

    i, j = 0, len(words) - 1

    while i < j and j >= 0 and i < len(words):
        try:
            swap(words, i, j)
        except ValueError as ve:
            print(ve)

        i += 1
        j -= 1

    return ' '.join(words)


def swap(words, i, j):
    if words is None or i < 0 or i >= len(words) or j < 0 or j >= len(words):
        raise ValueError('Invalid arguments to function swap()')

    words[i], words[j] = words[j], words[i]


def main():
    str1 = 'geeks quiz practice code'
    str2 = 'getting good at coding needs a lot of practice'

    print(str1)
    print(reverse_words_in_string(str1))

    print(str2)
    print(reverse_words_in_string(str2))


if __name__ == '__main__':
    main()