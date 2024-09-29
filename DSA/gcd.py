# The Greatest Common Divisor (GCD) of two numbers is the largest number that divides both of them without leaving a remainder.
# Division-based Euclidean algorithm.

def gcd(a: int, b: int) -> int:
    while a and b:
        if a < b:
            a, b = b, a
        a = a % b

    return b if a == 0 else a

# The Least Common Multiple (LCM) of two numbers is the smallest non-zero number that is a multiple of both.
def lcm(a: int, b: int) -> int:
    return abs(a * b) // gcd(a, b)

def main():
    print(gcd(48, 18))
    print(lcm(15, 12))

if __name__ == "__main__":
    main()
