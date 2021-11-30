//
// Created by cpepi on 27-Oct-21.
//

#include "VertexHeap.hpp"

VertexHeap::VertexHeap() {
    size = 0;
    for (int i = 0; i < N; ++i) {
        P[i] = -1;
        HD[i] = Vertex();
    }
}

Vertex VertexHeap::max() {
    return HD[0];
}

bool VertexHeap::empty() {
    return size == 0;
}

void VertexHeap::print() {
    std::cout << "\nH\t";

    for (int i = 0; i < size; ++i) {
        std::cout << HD[i].id << "\t";
    }

    std::cout << std::endl << "D\t";
    for (int i = 0; i < size; ++i) {
        std::cout << HD[i].capacity << "\t";
    }

    std::cout << std::endl << "P\t";
    for (int i = 0; i < size; ++i) {
        std::cout << P[i] << "\t";
    }

    std::cout << std::endl;
}

void VertexHeap::insert(int v, int w) {
    if (P[v] != -1) {
        std::cout << "Vertex " << v << " is already in the heap. Abort insert." << std::endl;
        return;
    }

    increment_size();
    HD[size - 1].id = v;
    HD[size - 1].capacity = w;
    P[HD[size - 1].id] = size - 1;

    bottom_up_heapify(size - 1);
}

void VertexHeap::remove(int in_vertex, Vertex *vertex) {
    int index = P[in_vertex];

    if (index == -1) {
        std::cout << "Vertex " << in_vertex << " is not in the heap. Abort remove." << std::endl;
        return;
    }

    if (vertex)
        *vertex = HD[index];

    decrement_size();
    HD[index] = HD[size];
    P[HD[size].id] = index;

    HD[size].id = -1;
    HD[size].capacity = -1;
    P[in_vertex] = -1;

    max_heapify(index);
}

void VertexHeap::increment_size() {
    size++;
}

void VertexHeap::decrement_size() {
    size--;
}

void VertexHeap::max_heapify(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && HD[left].capacity > HD[largest].capacity) {
        largest = left;
    }

    if (right < size && HD[right].capacity > HD[largest].capacity) {
        largest = right;
    }

    if (index != largest) {
        swap(index, largest);
        max_heapify(largest);
    }
}

void VertexHeap::bottom_up_heapify(int index) {
    int parent = (index - 1) / 2;
    if (HD[parent].capacity > 0) {
        if (HD[index].capacity > HD[parent].capacity) {
            swap(index, parent);

            bottom_up_heapify(parent);
        }
    }
}

void VertexHeap::swap(int index_1, int index_2) {
    std::swap(HD[index_1], HD[index_2]);
    std::swap(P[HD[index_1].id], P[HD[index_2].id]);
}
