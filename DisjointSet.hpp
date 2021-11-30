//
// Created by cpepi on 08-Nov-21.
//

#ifndef CSCE_629_DISJOINTSET_HPP
#define CSCE_629_DISJOINTSET_HPP


#include <iostream>

#include "Parameters.hpp"

class DisjointSet {
private:
    int rank[N];

    int daddy[N];

public:
    DisjointSet();

    void print();

    int find(int vertex);

    void make_set(int vertex);

    void join(int vertex_1, int vertex_2);
};


#endif //CSCE_629_DISJOINTSET_HPP
