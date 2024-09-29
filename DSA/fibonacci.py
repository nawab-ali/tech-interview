# Fibonacci series
# fibonacci(n) = fibonacci(n - 1) + fibonacci(n - 2)

def fibonacci(n: int) -> list[int]:
    if n < 1:
        return []
    elif n == 1:
        return [0]
    else:
        fib = [0, 1]
        for i in range(2, n):
            fib.append(fib[i - 1] + fib[i - 2])
    
    return fib

def main():
    for i in range(-1, 10):
        print(fibonacci(i))

if __name__ == "__main__":
    main()
