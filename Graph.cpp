//
// Created by cpepi on 29-Oct-21.
//

#include "Graph.hpp"

Graph::Graph(int min_neighbours_to_connect, int max_neighbours_to_connect) {
    random = new Random(min_neighbours_to_connect, max_neighbours_to_connect);
    max_neighbours = max_neighbours_to_connect;
    n_edges = 0;

    connect_graph();
    generate_graph();
}

void Graph::print() {
    for (int v = 0; v < N; ++v) {
        std::cout << v << " -> ";
        std::queue<Vertex> temp_queue = adjacency_list[v];
        while (!temp_queue.empty()) {
            Vertex temp_vertex = temp_queue.front();
            temp_queue.pop();

            if (temp_queue.empty())
                std::cout << "[" << temp_vertex.id << ", " << temp_vertex.capacity << "]";
            else
                std::cout << "[" << temp_vertex.id << ", " << temp_vertex.capacity << "] -> ";
        }
        std::cout << std::endl;
    }
}

int Graph::get_number_of_edges(){
    return n_edges;
}

void Graph::add_edge(int v, int w) {
    n_edges++;

    Vertex vertex;
    vertex.capacity = random->get_capacity();;

    vertex.id = w;
    connected[v].insert(w);
    adjacency_list[v].push(vertex);

    vertex.id = v;
    connected[w].insert(v);
    adjacency_list[w].push(vertex);
}

void Graph::connect_graph() {
    for (int i = 0; i < N - 1; ++i)
        add_edge(i, i + 1);
    add_edge(N - 1, 0);
}

void Graph::generate_graph() {
    unsigned int neighbours;

    for (int v = 0; v < N; ++v) {
        connected[v].insert(v);
        if (v == 0) {
            connected[v].insert(N - 1);
            connected[v].insert(v + 1);
        } else if (v == N - 1) {
            connected[v].insert(0);
            connected[v].insert(v - 1);
        } else {
            connected[v].insert(v - 1);
            connected[v].insert(v + 1);
        }

        neighbours = random->get_neighbours();
            while (neighbours != 0) {
                int w = random->get_vertex();
                if (!(connected[v].find(w) != connected[v].end())) {
                    add_edge(v, w);
                    neighbours--;
                }
            }
    }
}

std::queue<Vertex> *Graph::get_adjacency_list() {
    return adjacency_list;
}
