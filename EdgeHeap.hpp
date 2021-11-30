//
// Created by cpepi on 08-Nov-21.
//

#ifndef CSCE_629_EDGEHEAP_HPP
#define CSCE_629_EDGEHEAP_HPP


#include <iostream>

typedef struct {
    int vertex_1;
    int vertex_2;
    int capacity;
} Edge;

class EdgeHeap {
private:
    Edge *heap;

    int heap_size;

public:
    EdgeHeap(int N);

    Edge get();

    int size();

    void sort();

    void print();

    void insert(Edge edge);

private:
    void increment_size();

    void decrement_size();

    void heapify(int size, int index);

    void bottom_up_heapify(int index);
};


#endif //CSCE_629_EDGEHEAP_HPP
