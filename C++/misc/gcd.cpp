/**
GCD(a, b)
**/

#include<ctime>
#include<cassert>
#include<iostream>
#include<algorithm>

using namespace std;

//Naive GCD implementation: O(n)
int gcd_slow(int a, int b) {
    int gcd = -1;

    for (int i = 1; i <= min(a, b); i++) {
        if (!(a % i) && !(b % i)) {
            //a and b are both divisible by i
            gcd = i;
        }
    }
    return (gcd);
}

//Fast GCD implementation: O(log n)
int gcd_fast(int a, int b) {
    if (a < b) {
        swap(a, b);
    }

    if (!b) {
        return (a);
    } else {
        return gcd_fast(b, a % b);
    }
}

int main(int argc, char **argv) {
    int limit = 10000000;
    srand(time(NULL));

    for (int i = 0; i < 100; i++) {
        int a = rand() % limit + 1;
        int b = rand() % limit + 1;

        assert(gcd_slow(a, b) == gcd_fast(a, b));
    }
    return (0);
}
