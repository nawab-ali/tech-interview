// This class models the graph ADT

#ifndef GRAPH_H
#define GRAPH_H

#include <tuple>
#include <queue>
#include <string>
#include <limits>
#include <random>
#include <vector>
#include <utility>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "disjoint_set.h"

using namespace std;

// edge_t represents an edge in a graph
typedef tuple<double, int, int> edge_t;

// edge_cost_t specifies if there is an edge between 2 vertices and its cost
typedef pair<bool, double> edge_cost_t;

// Data structure used in shortest path calculation
typedef pair<double, int> spth_t;

class Graph {
private:
    bool directed;
    int num_vertices;
    vector <vector<edge_cost_t>> adj_matrix;

    void populate_default_graph(void);
    bool is_cycle(DisjointSet &ds, const edge_t &e);

public:
    Graph(const bool directed = false, const int num_vertices = 0);
    Graph(const bool directed, const int num_vertices, const double edge_density, const double weight_range);
    Graph(const bool directed, const string &filename);

    bool is_directed(void);
    int V(void);    // #vertices
    long E(void);    // #edges
    bool adjacent(const int u, const int v);
    vector<int> neighbors(const int u);
    bool add_edge(const int u, const int v, const double weight);
    bool delete_edge(const int u, const int v);
    double get_edge_weight(const int u, const int v);
    void set_edge_weight(const int u, const int v, const double weight);
    void random_graph(const double edge_density, const double weight_range);
    vector<double> shortest_path(const int u);
    vector <edge_t> mst(void);
    void clear(void);

    // Overload the << operator
    friend ostream &operator<<(ostream &out, const Graph &g) {
        for (int i = 0; i < g.num_vertices; i++) {
            for (int j = 0; j < g.num_vertices; j++) {
                out << "<" << g.adj_matrix[i][j].first << ", " <<
                    g.adj_matrix[i][j].second << ">" << " ";
            }
            out << endl;
        }
        return out;
    }
};

// Populate the graph with default values
void Graph::populate_default_graph(void) {
    assert(num_vertices >= 0);

    for (int i = 0; i < num_vertices; i++) {
        vector <edge_cost_t> v;
        adj_matrix.push_back(v);
        for (int j = 0; j < num_vertices; j++) {
            adj_matrix[i].push_back(make_pair(false, 0.0));
        }
    }
}

// Does edge e create a cycle in the spanning tree?
bool Graph::is_cycle(DisjointSet &ds, const edge_t &e) {
    int i = get<1>(e);
    int j = get<2>(e);

    return (ds.find(i) == ds.find(j));
}

// Constructor
Graph::Graph(const bool directed, const int num_vertices) {
    assert(num_vertices >= 0);
    this->directed = directed;
    this->num_vertices = num_vertices;

    // Populate the graph with default values
    populate_default_graph();
}

// Constructor to generate random edges in the graph
Graph::Graph(const bool directed, const int num_vertices, const double edge_density, const double weight_range) :
             Graph(directed, num_vertices) {
    random_graph(edge_density, weight_range);
}

// Constructor to generate a graph from an input text file
Graph::Graph(const bool directed, const string &filename) {
    string line;
    int line_num = 0;

    this->directed = directed;

    // Process the input file
    ifstream file(filename);
    assert(file.is_open());

    while (getline(file, line)) {
        if (line_num == 0) {
            // First line contains the number of vertices in graph
            this->num_vertices = stoi(line);
            assert(this->num_vertices >= 0);

            // Populate the graph with default values
            populate_default_graph();
        } else {
            // Subsequent lines contain edge costs (i, j, cost)
            int i, j, cost;
            istringstream iss(line);
            vector <string> tokens{istream_iterator < string > {iss},
                                   istream_iterator < string > {}};
            i = stoi(tokens[0]);
            j = stoi(tokens[1]);
            cost = stoi(tokens[2]);
            add_edge(i, j, cost);
        }
        line_num++;
    }
    file.close();
}

// Is it a directed graph?
bool Graph::is_directed(void) {
    return (directed);
}

// Return the number of vertices in the graph
int Graph::V(void) {
    return (num_vertices);
}

// Return the number of edges in the graph
long Graph::E(void) {
    long num_edges = 0;

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (adj_matrix[i][j].first) {
                num_edges++;
            }
        }
    }

    return (num_edges);
}

// Test whether there is an edge from node u to node v
bool Graph::adjacent(const int u, const int v) {
    assert(u >= 0 && u < num_vertices);
    assert(v >= 0 && v < num_vertices);
    return (adj_matrix[u][v].first);
}

// Lists all nodes v such that there is an edge from u to v
vector<int> Graph::neighbors(const int u) {
    assert(u >= 0 && u < num_vertices);
    vector<int> v;

    for (int i = 0; i < num_vertices; i++) {
        if (adj_matrix[u][i].first) {
            v.push_back(i);
        }
    }

    return (v);
}

// Add edge from u to v, if it is not there
bool Graph::add_edge(const int u, const int v, const double weight = 0.0) {
    assert(u >= 0 && u < num_vertices);
    assert(v >= 0 && v < num_vertices);
    assert(u != v);

    if (adj_matrix[u][v].first) {
        // edge <u, v> exists
        return (false);
    } else {
        // edge <u, v> does not exist
        edge_cost_t ec = make_pair(true, weight);
        adj_matrix[u][v] = ec;
        if (!directed) {
            adj_matrix[v][u] = ec;
        }
        return (true);
    }
}

// Delete the edge from u to v, if it is there
bool Graph::delete_edge(const int u, const int v) {
    assert(u >= 0 && u < num_vertices);
    assert(v >= 0 && v < num_vertices);

    if (adj_matrix[u][v].first) {
        // edge <u, v> exists
        edge_cost_t ec = make_pair(false, 0.0);
        adj_matrix[u][v] = ec;
        if (!directed) {
            adj_matrix[v][u] = ec;
        }
        return (true);
    } else {
        // edge <u, v> does not exist
        return (false);
    }
}

// Returns the weight associated with the edge (u, v)
double Graph::get_edge_weight(const int u, const int v) {
    assert(u >= 0 && u < num_vertices);
    assert(v >= 0 && v < num_vertices);
    assert(adj_matrix[u][v].first);

    return (adj_matrix[u][v].second);
}

// Set the weight associated with the edge (u, v)
void Graph::set_edge_weight(const int u, const int v, const double weight) {
    assert(u >= 0 && u < num_vertices);
    assert(v >= 0 && v < num_vertices);

    assert(adj_matrix[u][v].first);
    adj_matrix[u][v].second = weight;

    if (!directed) {
        assert(adj_matrix[v][u].first);
        adj_matrix[v][u].second = weight;
    }
}

// Generate a random set of edges based on edge_density and weight_range
void Graph::random_graph(const double edge_density, const double weight_range) {
    assert(edge_density >= 0 && edge_density <= 1);
    assert(weight_range >= 0);

    // Random number generator
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> edge_prob(0.0, 1.0);
    uniform_real_distribution<double> edge_weight(0.0, weight_range);

    // Clear the graph edges
    clear();

    // Generate random edge probabilities and weights
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (i == j) continue;
            if (edge_prob(generator) < edge_density) {
                add_edge(i, j, edge_weight(generator));
            }
        }
    }
}

// Calculate the shortest path from vertex u to all other vertices using
// Dijkstra's algorithm
vector<double> Graph::shortest_path(const int u) {
    priority_queue <spth_t, vector<spth_t>, greater<spth_t>> pq;
    vector<double> distance(num_vertices, numeric_limits<double>::infinity());

    assert(u >= 0 && u < num_vertices);

    // Set the distance of u to 0 and push it into the priority queue
    distance[u] = 0.0;
    pq.push(make_pair(0.0, u));

    // Run until pq is empty
    while (!pq.empty()) {
        int u = 0;
        vector<int> neighbors_list;

        // Get the vertex with the shortest distance from source
        u = pq.top().second;
        pq.pop();

        // Get the neighbors of current vertex
        neighbors_list = neighbors(u);

        // Update the neighbors' shortest distance from source
        for (int i = 0; i < neighbors_list.size(); i++) {
            int v = neighbors_list[i];
            double edge_weight = get_edge_weight(u, v);

            if (distance[v] > distance[u] + edge_weight) {
                distance[v] = distance[u] + edge_weight;
                pq.push(make_pair(distance[v], v));
            }
        }
    }

    return (distance);
}

// Find a minimum spanning tree using Kruskal's algorithm
vector <edge_t> Graph::mst(void) {
    int i = 0;
    DisjointSet ds(V());
    vector <edge_t> edges;
    vector <edge_t> mst_edges;

    assert(!is_directed());

    // Store the set of edges in the graph
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (adj_matrix[i][j].first) {
                edges.push_back(make_tuple(adj_matrix[i][j].second, i, j));
            }
        }
    }

    // Sort the edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end());

    // Pick the smallest edge. Check if it forms a cycle with the spanning
    // tree formed so far. If cycle is not formed, include this edge. Else,
    // discard it. Repeat until there are (V-1) edges in the spanning tree.
    while (mst_edges.size() != (V() - 1)) {
        // MST has V-1 edges
        edge_t e = edges[i++];
        if (!is_cycle(ds, e)) {
            mst_edges.push_back(e);
            ds.merge(get<1>(e), get<2>(e));
        }
    }

    assert(mst_edges.size() == V() - 1);

    return (mst_edges);
}

// Clear the edges in the graph
void Graph::clear(void) {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            delete_edge(i, j);
        }
    }
}

#endif //GRAPH_H
