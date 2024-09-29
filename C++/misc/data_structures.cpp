#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

void vector_tests(void) {
    vector<int> v1, v3;
    vector<double> v2(10);

    for (int i = 0; i < 10; i++) {
        v1.push_back(i);
        cout << v1[i] << " ";
    }
    cout << endl;
    cout << v1.size() << endl;

    v3 = v1;

    for (int i = 0; i < 10; i++) {
        v1.pop_back();
        cout << v1.size() << endl;
    }

    v3.erase(v3.begin() + 2);
    v3.insert(v3.begin() + 2, 17);
    for (const auto &n : v3) {
        cout << n << " ";
    }
    cout << endl;
}

void stack_tests(void) {
    stack<int> s;

    for (int i = 0; i < 10; i++) {
        s.push(i);
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

void queue_tests(void) {
    queue<int> q;

    for (int i = 0; i < 10; i++) {
        q.push(i);
    }

    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

void umap_tests(void) {
    unordered_map<string, double> umap;

    umap["pi"] = 3.14;
    umap["root2"] = 1.414;
    umap["root3"] = 1.732;
    umap["log10"] = 2.302;
    umap["loge"] = 1.0;

    for (const auto &p : umap) {
        cout << p.first << ":" << p.second << endl;
    }

    umap.erase("log10");

    for (const auto &p : umap) {
        cout << p.first << ":" << p.second << endl;
    }
}

int main(int argc, char **argv) {
    //vector_tests();
    //stack_tests();
    //queue_tests();
    umap_tests();

    return 0;
}