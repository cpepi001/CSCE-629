cmake_minimum_required(VERSION 3.10)
project(CSCE_629)

set(CMAKE_CXX_STANDARD 14)

add_executable(CSCE_629 main.cpp VertexHeap.cpp VertexHeap.hpp Graph.cpp Graph.hpp Random.cpp Random.hpp Algorithms.cpp Algorithms.hpp Parameters.hpp EdgeHeap.cpp EdgeHeap.hpp DisjointSet.cpp DisjointSet.hpp)
