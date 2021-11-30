//
// Created by cpepi on 27-Oct-21.
//

#ifndef CSCE_629_VERTEXHEAP_HPP
#define CSCE_629_VERTEXHEAP_HPP


#include <iostream>

#include "Parameters.hpp"

typedef struct {
    int id;
    int capacity;
} Vertex;

class VertexHeap {
private:
    int P[N];

    int size;

    Vertex HD[N];

public:
    VertexHeap();

    Vertex max();

    bool empty();

    void print();

    void insert(int vertex, int bandwidth);

    void remove(int in_vertex, Vertex *vertex = nullptr);

private:

    void increment_size();

    void decrement_size();

    void max_heapify(int index);

    void bottom_up_heapify(int index);

    void swap(int index_1, int index_2);
};


#endif //CSCE_629_VERTEXHEAP_HPP
