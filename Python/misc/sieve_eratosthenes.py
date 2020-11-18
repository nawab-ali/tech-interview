# Given a small number n, print all primes smaller than or equal to n.

def gen_smaller_primes(n):
    if n < 1:
        raise ValueError('n < 1')

    p = 2
    primes = [True] * (n + 1)
    primes[0], primes[1] = False, False

    while p * p <= n:
        if primes[p] is True:
            # Update all multiples of p
            for i in range(p * p, n + 1, p):
                primes[i] = False
        p += 1

    return [i for i in range(len(primes)) if primes[i] is True]


def main():
    try:
        primes = gen_smaller_primes(0)
        print(primes)
    except ValueError as ve:
        print(ve)


if __name__ == '__main__':
    main()