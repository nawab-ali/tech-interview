#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    bitset<8> bs1;
    bitset<8> bs2(2);
    bitset<1> bs3(1);
    bitset<4> bs4(string("1101"));

    cout << "bs1: " << bs1 << endl;
    cout << "bs2: " << bs2 << endl;
    cout << "bs3: " << bs3 << endl;
    cout << "bs4: " << bs4 << endl;

    bs1[7] = 1;
    cout << "bs1: " << bs1 << endl;

    cout << "bs4 #set_bits: " << bs4.count() << endl;
    cout << "bs4 #unset_bits: " << bs4.size() - bs4.count() << endl;

    for (long unsigned int i = 0; i < bs4.size(); i++) {
        cout << "bs4[i]: " << bs4.test(i) << endl;
    }

    cout << "Reset bs1: " << bs1.reset() << endl;
    cout << "Set bs1: " << bs1.set() << endl;
    cout << "Flip bs1: " << bs1.flip() << endl;
    cout << "Flip bs1[2]: " << bs1.flip(2) << endl;

    cout << "bs1 & bs2: " << (bs1 & bs2) << endl;
    cout << "bs1 | bs2: " << (bs1 | bs2) << endl;
    cout << "bs1 ^ bs2: " << (bs1 ^ bs2) << endl;
    cout << "~bs1: " << (~bs1) << endl;
    cout << "bs1 << 2: " << (bs1 << 2) << endl;
    cout << "bs1 >> 2: " << (bs1 >> 2) << endl;

    return 0;
}
