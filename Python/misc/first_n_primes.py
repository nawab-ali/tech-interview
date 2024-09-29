# Print the first N prime numbers

def gen_first_n_primes(n):
    if n < 0:
        raise ValueError('n < 0')

    i = 2
    primes = []

    while len(primes) < n:
        if is_prime(i, primes):
            primes.append(i)
        i += 1

    return primes


def is_prime(n, primes):
    if n < 1 or primes is None:
        raise ValueError('n < 1 or primes is None')

    for prime in primes:
        if n % prime == 0:
            return False
    return True


def main():
    print(gen_first_n_primes(1000))


if __name__ == '__main__':
    main()