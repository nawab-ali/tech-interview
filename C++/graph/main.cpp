// main.cpp

#include "disjoint_set.h"
#include "graph_sim.h"

int main(int argc, char **argv) {
    double mst_cost = 0.0;
    vector<edge_t> mst_edges;

    GraphSim g_sim(100, 100, 100.0, 0.2);
    vector<double> v = g_sim.sim_shortest_path();

    for (int i = 0; i < v.size(); i++) {
        cout << i << " " << v[i] << endl;
    }

    Graph g(false, "mst_data.txt");
    mst_edges = g.mst();

    for (int i = 0; i < mst_edges.size(); i++) {
        edge_t e = mst_edges[i];
        cout << get<1>(e) << " " << get<2>(e) << " " << get<0>(e) << endl;
        mst_cost += get<0>(e);
    }
    cout << mst_cost << endl;

    return (0);
}
