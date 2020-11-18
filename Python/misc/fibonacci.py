# Print the first 1000 Fibonacci numbers
# Fib(0) = 0
# Fib(1) = 1
# Fib(n) = Fib(n-1) + Fib(n-2)

def fibonacci(n):
    if n < 0:
        raise ValueError('n < 0')

    fib = [None] * n
    fib[0], fib[1] = 0, 1

    for i in range(2, n):
        fib[i] = fib[i - 1] + fib[i - 2]

    return fib


def main():
    try:
        fib = fibonacci(100)
        print(fib)
    except ValueError as ve:
        print(ve)


if __name__ == '__main__':
    main()