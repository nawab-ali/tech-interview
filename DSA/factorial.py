# Factorial
def factorial(n: int) -> int:
    if n < 0:
        raise ValueError("Factorial is not defined for negative numbers")
    else:
        result = 1
        for i in range(2, n + 1):
            result *= i

    return result

# Factorial implemented recursively
def factorial_recursive(n: int) -> int:
    if n < 0:
        raise ValueError("Factorial is not defined for negative numbers")
    elif n == 0:
        return 1
    else:
        return n * factorial_recursive(n - 1)

def main():
    for i in range(-1, 10):
        try:
            print(factorial(i), factorial_recursive(i))
        except ValueError as e:
            print(e)

if __name__ == "__main__":
    main()
