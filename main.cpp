#include "Algorithms.hpp"

int main() {
    Graph graph(1, 4);

    std::queue<Vertex> *temp = graph.get_adjacency_list();

    unsigned long edges = 0;
    for (int i = 0; i < N; ++i) {
        edges += temp[i].size();
    }

    std::cout << edges / N << std::endl;

    Algorithms::Dijkstra(graph.get_adjacency_list());
    Algorithms::OptimisedDijkstra(graph.get_adjacency_list());
    Algorithms::Kruskal(graph.get_adjacency_list(), graph.get_number_of_edges());

    return 0;
}
