# Rabin-Karp algorithm for finding patterns in text

def poly_hash(key, x = 256, p = 1000000007):
    """ Return hash of key """

    hash_val = 0
    for i in range(len(key)):
        hash_val += (ord(key[i]) * pow(x, i))
        hash_val %= p

    return hash_val

def precompute_text_hash(text, pattern, x = 256, p = 1000000007):
    """ Precompute the hash of all substrings of 'text' of len(pattern) """

    assert(text is not None and pattern is not None)
    assert(len(text) >= len(pattern))

    n = len(text)
    m = len(pattern)
    y = pow(x, m) % p
    text_substr_hashes = [[None, None, None] for i in range(n-m+1)]

    text_substr_hashes[n-m] = [n-m, text[n-m:n], poly_hash(text[n-m:n])]

    for i in range(n-m-1, -1, -1):
        hash_val = (x*text_substr_hashes[i+1][2] + ord(text[i]) - y*ord(text[i+m])) % p
        text_substr_hashes[i] = [i, text[i:i+m], hash_val]

    return text_substr_hashes

def search(text, pattern):
    """ Search for 'pattern' in 'text' """

    assert(text is not None and pattern is not None)
    assert(len(text) >= len(pattern))

    match = []
    n = len(text)
    m = len(pattern)

    pattern_hash = poly_hash(pattern)
    precomputed_text_hashes = precompute_text_hash(text, pattern)

    # Compare all the text substrings with pattern. If the hashes don't match,
    # we continue. If the hashes match, we compare the substring with the
    # pattern to confirm match.
    for i in range(len(precomputed_text_hashes)):
        index, substr, substr_hash = precomputed_text_hashes[i]
        if substr_hash == pattern_hash:
            if substr == pattern:
                match.append(index)
    return match

def main():
    print(search('baaaaaaa', 'aaaaa'))

if __name__ == '__main__':
    main()
