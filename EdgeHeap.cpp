//
// Created by cpepi on 08-Nov-21.
//

#include "EdgeHeap.hpp"

EdgeHeap::EdgeHeap(int Nn) {
    heap_size = 0;
    heap = new Edge[Nn];
}

Edge EdgeHeap::get() {
    decrement_size();
    return heap[heap_size];
}

int EdgeHeap::size() {
    return heap_size;
}

void EdgeHeap::sort() {
    for (int i = heap_size - 1; i >= 0; i--) {
        std::swap(heap[0], heap[i]);
        heapify(i, 0);
    }
}

void EdgeHeap::print() {
    std::cout << "\nH\t";
    for (int i = 0; i < heap_size; ++i) {
        std::cout << heap[i].capacity << "\t";
    }
    std::cout << std::endl;
}

void EdgeHeap::insert(Edge edge) {
    increment_size();

    heap[heap_size - 1] = edge;
    bottom_up_heapify(heap_size - 1);
}

void EdgeHeap::increment_size() {
    heap_size++;
}

void EdgeHeap::decrement_size() {
    heap_size--;
}

void EdgeHeap::heapify(int n, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && heap[left].capacity > heap[largest].capacity) {
        largest = left;
    }

    if (right < n && heap[right].capacity > heap[largest].capacity) {
        largest = right;
    }

    if (index != largest) {
        std::swap(heap[index], heap[largest]);
        heapify(n, largest);
    }
}

void EdgeHeap::bottom_up_heapify(int index) {
    int parent = (index - 1) / 2;
    if (heap[parent].capacity > 0) {
        if (heap[index].capacity > heap[parent].capacity) {
            std::swap(heap[index], heap[parent]);

            bottom_up_heapify(parent);
        }
    }
}
