#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    set<int, less<int>> s1 = {2, 3, 4, 5, 6, 6, 6, 7, 5,
                              7, 8, 9, 3, 4, 2, 4, 5, 6};
    set<int, less<int>> s2 = {2, 3, 9, 5, 2, 10};
    vector<int> v(20);

    // sort(v.begin(), v.end());

    cout << "s1: ";
    for (const auto &s : s1) {
        cout << s << " ";
    }
    cout << endl;

    cout << "s2: ";
    for (const auto &s : s2) {
        cout << s << " ";
    }
    cout << endl;

    auto it = set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), v.begin());

    cout << "s1 union s2: ";
    for (auto st = v.begin(); st != it; st++) {
        cout << *st << " ";
    }
    cout << endl;

    it =
        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), v.begin());

    cout << "s1 intersection s2: ";
    for (auto st = v.begin(); st != it; st++) {
        cout << *st << " ";
    }
    cout << endl;

    it = set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), v.begin());

    cout << "s1-s2: ";
    for (auto st = v.begin(); st != it; st++) {
        cout << *st << " ";
    }
    cout << endl;

    return 0;
}
