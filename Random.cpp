//
// Created by cpepi on 30-Oct-21.
//

#include "Random.hpp"

Random::Random(int min_neighbours_to_connect, int max_neighbours_to_connect) {
    mt19937 = std::mt19937(random_device());
    vertex_distribution = std::uniform_int_distribution<>(0, N - 1);
    capacity_distribution = std::uniform_int_distribution<>(MIN_CAPACITY, MAX_CAPACITY);
    neighbours_distribution = std::uniform_int_distribution<>(min_neighbours_to_connect, max_neighbours_to_connect);
}

int Random::get_vertex() {
    return vertex_distribution(mt19937);
}

int Random::get_capacity() {
    return capacity_distribution(mt19937);
}

int Random::get_neighbours() {
    return neighbours_distribution(mt19937);
}
