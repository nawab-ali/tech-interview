#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/**
void heapsort(vector<int> &v) {
    for (long unsigned int i = 0; i < v.size(); i++) {
        make_heap(v.begin() + i, v.end());
    }
}
**/

void heapsort(vector<int> &v) {
    int i = 0;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (const auto &e : v) {
        pq.push(e);
    }

    while (!pq.empty()) {
        v[i++] = pq.top();
        pq.pop();
    }
}

int main(int argc, char **argv) {
    vector<int> v = {2, 7, 9, 4, 5, 8, 1, 3, 6, 10};

    heapsort(v);

    for (const auto &e : v) {
        cout << e << " ";
    }

    cout << endl;

    return (0);
}