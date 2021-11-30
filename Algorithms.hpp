//
// Created by cpepi on 05-Nov-21.
//

#ifndef CSCE_629_ALGORITHMS_HPP
#define CSCE_629_ALGORITHMS_HPP


#include <stack>
#include <chrono>

#include "Graph.hpp"
#include "DisjointSet.hpp"

class Algorithms {
public:
    static void Dijkstra(std::queue<Vertex> *adjacency_list);

    static void OptimisedDijkstra(std::queue<Vertex> *adjacency_list);

    static void Kruskal(std::queue<Vertex> *adjacency_list, int n_edges);

private:
    Algorithms();

    static void BFS(std::queue<Vertex> *adjacency_list, EdgeHeap &edges_heap);

    enum COLOR_CODE {WHITE, GREY, BLACK};

    enum VERTEX_STAGE {UNSEEN, FRINGE, IN_TREE};
};


#endif //CSCE_629_ALGORITHMS_HPP
