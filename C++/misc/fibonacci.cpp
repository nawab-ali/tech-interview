/**
Fibonacci series
F(0) = 0
F(1) = 1
F(n) = F(n-1) + F(n-2)
**/

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

long long fibonacci_slow(int n) {
    // Naive and slow implementation
    if (n <= 1) {
        return n;
    } else {
        return (fibonacci_slow(n - 1) + fibonacci_slow(n - 2));
    }
}

long long fibonacci_fast(int n) {
    // Fast implementation
    vector<long long> v(n + 1);

    v[0] = 0;
    v[1] = 1;

    for (int i = 2; i < n + 1; i++) {
        v[i] = v[i - 1] + v[i - 2];
    }
    return (v[n]);
}

int main(int argc, char **argv) {
    int limit = 30;
    srand(time(0));

    for (int i = 0; i < 100; i++) {
        int n = rand() % limit + 1;
        assert(fibonacci_slow(n) == fibonacci_fast(n));
    }
    return (0);
}
