// Count the number of set bits in an integer

#include <iostream>

using namespace std;

int pop_count(int n) {
    int count = 0;

    for (long unsigned int i = 0; i < sizeof(n) * 8; i++) {
        if (1 & n) {
            count++;
        }
        n >>= 1;
    }

    return (count);
}

int main(int argc, char **argv) {
    int n = -1;
    cout << "n: " << n << " #setbits: " << pop_count(n) << endl;
    return (0);
}
