// This class models the Monte Carlo simulation for shortest paths in a graph

#ifndef GRAPH_SIM_H
#define GRAPH_SIM_H

#include "graph.h"

class GraphSim {
private:
    int sim_iterations;
    int graph_vertices;
    double graph_weight_max;
    double graph_edge_density;

public:
    GraphSim(const int sim_iterations, const int graph_vertices, const double graph_weight_max,
             const double graph_edge_density);

    int get_sim_iterations(void);
    int get_graph_vertices(void);
    double get_graph_weight_max(void);
    double get_graph_edge_density(void);
    void set_sim_iterations(const int sim_iterations);
    void set_graph_weight_max(const double graph_weight_max);
    void set_graph_edge_density(const double graph_edge_density);
    vector<double> sim_shortest_path(void);
};

// Constructor
GraphSim::GraphSim(const int sim_iterations, const int graph_vertices, const double graph_weight_max,
                   const double graph_edge_density = 0.1) {
    assert(sim_iterations > 0);
    assert(graph_vertices > 0);
    assert(graph_weight_max > 0);
    assert(graph_edge_density >= 0 && graph_edge_density <= 1);

    this->sim_iterations = sim_iterations;
    this->graph_vertices = graph_vertices;
    this->graph_weight_max = graph_weight_max;
    this->graph_edge_density = graph_edge_density;
}

// Return the number of simulation iterations
int GraphSim::get_sim_iterations(void) {
    return (sim_iterations);
}

// Return the number of vertices in the graph
int GraphSim::get_graph_vertices(void) {
    return (graph_vertices);
}

// Return the graph_weight_max
double GraphSim::get_graph_weight_max(void) {
    return (graph_weight_max);
}

// Return the graph_edge_density
double GraphSim::get_graph_edge_density(void) {
    return (graph_edge_density);
}

// Set the sim_iterations
void GraphSim::set_sim_iterations(const int sim_iterations) {
    assert(sim_iterations > 0);
    this->sim_iterations = sim_iterations;
}

// Set the graph_weight_max
void GraphSim::set_graph_weight_max(const double graph_weight_max) {
    assert(graph_weight_max > 0);
    this->graph_weight_max = graph_weight_max;
}

// Set the graph_edge_density
void GraphSim::set_graph_edge_density(const double graph_edge_density) {
    assert(graph_edge_density >= 0 && graph_edge_density <= 1);
    this->graph_edge_density = graph_edge_density;
}

// Monte Carlo simulation for shortest paths in a graph
vector<double> GraphSim::sim_shortest_path(void) {
    double avg_spth = 0.0;
    vector<double> spth, sim_spth;
    Graph g(false, graph_vertices);

    for (int i = 0; i < sim_iterations; i++) {
        g.random_graph(graph_edge_density, graph_weight_max);
        spth = g.shortest_path(0);
        avg_spth = accumulate(spth.begin(), spth.end(), 0.0) / spth.size();
        sim_spth.push_back(avg_spth);
    }

    return (sim_spth);
}

#endif //GRAPH_SIM_H
