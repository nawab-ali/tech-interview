// This class models the Disjoint Set data structure

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class DisjointSet {
  private:
    vector<int> parent;
    vector<int> rank;

  public:
    DisjointSet(const int n);
    int find(const int x);
    void merge(const int x, const int y);

    // Overload the << operator
    friend ostream &operator<<(ostream &out, const DisjointSet &s) {
        out << "Parent: ";
        for (int i = 0; i < s.parent.size(); i++) {
            out << s.parent[i] << " ";
        }
        out << endl;

        out << "Rank:   ";
        for (int i = 0; i < s.rank.size(); i++) {
            out << s.rank[i] << " ";
        }
        out << endl;
        return (out);
    }
};

// Constructor
DisjointSet::DisjointSet(const int n) {
    assert(n >= 0);
    rank.assign(n, 0);
    for (int i = 0; i < n; i++) {
        parent.push_back(i);
    }
}

// Return the root (representative) of x using path compression
int DisjointSet::find(const int x) {
    assert(x >= 0 && x < parent.size());

    // Find x with path compression
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }

    return (parent[x]);
}

// Merge the 2 sets using union by rank
void DisjointSet::merge(const int x, const int y) {
    assert(x >= 0 && x < parent.size());
    assert(y >= 0 && y < parent.size());

    int x_root = find(x);
    int y_root = find(y);

    assert(x_root >= 0 && x_root < parent.size());
    assert(y_root >= 0 && y_root < parent.size());

    // x, y belong to the same set already
    if (x_root == y_root) {
        return;
    }

    if (rank[x_root] < rank[y_root]) {
        // Attach smaller rank tree under the root of high rank tree
        parent[x_root] = y_root;
    } else if (rank[x_root] > rank[y_root]) {
        parent[y_root] = x_root;
    } else {
        // If ranks are the same, make one the root and increment its rank
        parent[y_root] = x_root;
        rank[x_root] += 1;
    }
}

#endif // DISJOINT_SET_H
