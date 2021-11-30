//
// Created by cpepi on 08-Nov-21.
//

#include <queue>
#include "DisjointSet.hpp"

DisjointSet::DisjointSet() {
    for (int i = 0; i < N; ++i) {
        make_set(i);
    }
}

void DisjointSet::print() {
    for (int i: rank) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (int i: daddy) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int DisjointSet::find(int vertex) {
    int w = vertex;
    while (daddy[w] != -1) {
        w = daddy[w];
    }

    return w;
}

void DisjointSet::make_set(int vertex) {
    rank[vertex] = 0;
    daddy[vertex] = -1;
}

void DisjointSet::join(int vertex_1, int vertex_2) {
    if (rank[vertex_1] > rank[vertex_2]) {
        daddy[vertex_2] = vertex_1;
    } else if (rank[vertex_2] > rank[vertex_1]) {
        daddy[vertex_1] = vertex_2;
    } else {
        daddy[vertex_2] = vertex_1;
        rank[vertex_1]++;
    }
}
