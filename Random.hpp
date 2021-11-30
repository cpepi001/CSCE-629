//
// Created by cpepi on 30-Oct-21.
//

#ifndef CSCE_629_RANDOM_HPP
#define CSCE_629_RANDOM_HPP


#include <random>

#include "Parameters.hpp"

class Random {
private:
    std::mt19937 mt19937;

    std::random_device random_device;

    std::uniform_int_distribution<> vertex_distribution;

    std::uniform_int_distribution<> capacity_distribution;

    std::uniform_int_distribution<> neighbours_distribution;

public:
    Random(int min_neighbours_to_connect, int max_neighbours_to_connect);

    int get_vertex();

    int get_capacity();

    int get_neighbours();
};


#endif //CSCE_629_RANDOM_HPP
