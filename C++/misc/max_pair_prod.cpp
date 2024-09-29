// Maximum pairwise product

#include<vector>
#include<cassert>
#include<cstdlib>
#include<iostream>

using namespace std;

long long max_pairwise_product_fast(const vector<int> &v) {
    //Fast implementation: O(n)
    int index1 = -1;
    int index2 = -1;

    for (int i = 0; i < v.size(); i++) {
        if ((index1 == -1) || (v[i] > v[index1])) {
            index1 = i;
        }
    }

    for (int i = 0; i < v.size(); i++) {
        if ((i != index1) && ((index2 == -1) || (v[i] > v[index2]))) {
            index2 = i;
        }
    }

    return (v[index1] * v[index2]);
}

long long max_pairwise_product_slow(const vector<int> &v) {
    //Naive implementation: O(n^2)
    int n = v.size();
    long long prod = 0;
    long long max_prod = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            prod = v[i] * v[j];
            if (prod > max_prod) max_prod = prod;
        }
    }
    return (max_prod);
}

int main(int argc, char **argv) {
    vector<int> v(10000);
    srand(time(0));

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < v.size(); j++) {
            v[j] = rand() % 40000 + 2;
        }
        assert(max_pairwise_product_slow(v) == max_pairwise_product_fast(v));
    }
    return (0);
}
