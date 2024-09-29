# Reverse words in the given string

def reverse_words(input: str) -> str:
    words_list = input.split()
    i, j = 0, len(words_list) - 1

    while i < len(words_list) and j >= 0 and i < j:
        words_list[i], words_list[j] = words_list[j], words_list[i]
        i = i + 1
        j = j - 1

    return ' '.join(words_list)

def reverse_words_efficient(input: str) -> str:
    words = input.split()
    reversed_words = words[::-1]
    return ' '.join(reversed_words)

def main():
    input = 'The quick brown fox'
    print(input)
    print(reverse_words(input))
    print(reverse_words_efficient(input))

if __name__ == "__main__":
    main()
