//
// Created by cpepi on 29-Oct-21.
//

#ifndef CSCE_629_GRAPH_HPP
#define CSCE_629_GRAPH_HPP


#include <set>
#include <queue>

#include "VertexHeap.hpp"
#include "Random.hpp"
#include "EdgeHeap.hpp"

class Graph {
private:
    int n_edges;

    Random *random;

    int max_neighbours;

    std::set<int> connected[N];

    std::queue<Vertex> adjacency_list[N];
public:
    Graph(int min_neighbours_to_connect, int max_neighbours_to_connect);

    void print();

    int get_number_of_edges();

    void add_edge(int v, int w);

    std::queue<Vertex> *get_adjacency_list();

private:
    void connect_graph();

    void generate_graph();
};


#endif //CSCE_629_GRAPH_HPP
