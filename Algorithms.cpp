//
// Created by cpepi on 05-Nov-21.
//

#include "Algorithms.hpp"

Algorithms::Algorithms() = default;

void Algorithms::BFS(std::queue<Vertex> *adjacency_list, EdgeHeap &edges_heap) {
    int daddy[N];
    int color[N];
    for (int v = 0; v < N; ++v) {
        daddy[v] = -1;
        color[v] = WHITE;
    }

    int v = 0;
    color[v] = BLACK;

    std::queue<int> queue;
    queue.push(v);

    while (!queue.empty()) {
        v = queue.front();
        queue.pop();

        if (color[v] == GREY) {
            color[v] = BLACK;
        }

        std::queue<Vertex> temp_queue = adjacency_list[v];
        for (unsigned long i = temp_queue.size(); i > 0; --i) {
            Vertex w = temp_queue.front();
            temp_queue.pop();

            if (color[w.id] == WHITE) {
                daddy[w.id] = v;

                queue.push(w.id);
                color[w.id] = GREY;
            }

            if (color[v] == BLACK && color[w.id] == BLACK) {
                Edge edge;
                edge.vertex_1 = v;
                edge.vertex_2 = w.id;
                edge.capacity = w.capacity;

                edges_heap.insert(edge);
            }
        }
    }

    edges_heap.sort();
}

void Algorithms::Dijkstra(std::queue<Vertex> *adjacency_list) {
    auto start = std::chrono::high_resolution_clock::now();
    std::queue<Vertex> fringes;

    int daddy[N];
    int status[N];
    int bandwidth[N];

    for (int v = 0; v < N; ++v) {
        daddy[v] = -1;
        bandwidth[v] = -1;
        status[v] = UNSEEN;
    }

    status[SOURCE] = IN_TREE;
    std::queue<Vertex> temp_queue = adjacency_list[SOURCE];
    while (!temp_queue.empty()) {
        Vertex temp = temp_queue.front();
        temp_queue.pop();
        fringes.push(temp);

        daddy[temp.id] = SOURCE;
        status[temp.id] = FRINGE;
        bandwidth[temp.id] = temp.capacity;
    }

    while (!fringes.empty()) {
        int v = -1;
        int max = -1;

        // Pick the fringe with the largest bandwidth
        for (unsigned long i = fringes.size(); i > 0; --i) {
            Vertex temp = fringes.front();
            fringes.pop();
            if (bandwidth[temp.id] > max) {
                max = bandwidth[temp.id];
                v = temp.id;
            }
            fringes.push(temp);
        }

        status[v] = IN_TREE;
        for (unsigned long i = fringes.size(); i > 0; --i) {
            Vertex temp = fringes.front();
            fringes.pop();
            if (temp.id != v) {
                fringes.push(temp);
            }
        }

        temp_queue = adjacency_list[v];
        while (!temp_queue.empty()) {
            Vertex w = temp_queue.front();
            temp_queue.pop();
            if (status[w.id] == UNSEEN) {
                fringes.push(w);

                daddy[w.id] = v;
                status[w.id] = FRINGE;
                bandwidth[w.id] = std::min(bandwidth[v], w.capacity);
            } else if (status[w.id] == FRINGE && bandwidth[w.id] < std::min(bandwidth[v], w.capacity)) {
                daddy[w.id] = v;
                bandwidth[w.id] = std::min(bandwidth[v], w.capacity);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Elapsed time in milliseconds: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " ms" << std::endl;

    if (status[DESTINATION] != IN_TREE) {
        std::cout << "No path from " << SOURCE << " to " << DESTINATION << std::endl;
        std::cout << "That's impossible! Something is wrong." << std::endl;
        return;
    } else {
        int bw = INFINITY;
        int x = DESTINATION;
        std::stack<int> path;

        path.push(x);
        if (bandwidth[x] < bw && bandwidth[x] != -1) {
            bw = bandwidth[x];
        }
        while (x != SOURCE) {
            x = daddy[x];
            path.push(x);

            if (bandwidth[x] < bw && bandwidth[x] != -1) {
                bw = bandwidth[x];
            }
        }

        while (!path.empty()) {
            x = path.top();
            path.pop();

            if (!path.empty()) {
                std::cout << x << " -> ";
            } else {
                std::cout << x << " with " << bw << " bandwidth" << std::endl;
            }
        }
    }
}

void Algorithms::OptimisedDijkstra(std::queue<Vertex> *adjacency_list) {
    auto start = std::chrono::high_resolution_clock::now();
    VertexHeap fringes;

    int daddy[N];
    int status[N];
    int bandwidth[N];

    for (int v = 0; v < N; ++v) {
        daddy[v] = -1;
        bandwidth[v] = -1;
        status[v] = UNSEEN;
    }

    status[SOURCE] = IN_TREE;
    std::queue<Vertex> temp_queue = adjacency_list[SOURCE];
    while (!temp_queue.empty()) {
        Vertex temp = temp_queue.front();
        temp_queue.pop();

        fringes.insert(temp.id, temp.capacity);

        daddy[temp.id] = SOURCE;
        status[temp.id] = FRINGE;
        bandwidth[temp.id] = temp.capacity;
    }

    while (!fringes.empty()) {
        Vertex v = fringes.max();
        fringes.remove(v.id);
        status[v.id] = IN_TREE;

        temp_queue = adjacency_list[v.id];
        while (!temp_queue.empty()) {
            Vertex w = temp_queue.front();
            temp_queue.pop();

            if (status[w.id] == UNSEEN) {
                fringes.insert(w.id, w.capacity);

                status[w.id] = FRINGE;
                daddy[w.id] = v.id;
                bandwidth[w.id] = std::min(bandwidth[v.id], w.capacity);
            } else if (status[w.id] == FRINGE && bandwidth[w.id] < std::min(bandwidth[v.id], w.capacity)) {
                fringes.remove(w.id);

                bandwidth[w.id] = std::min(bandwidth[v.id], w.capacity);
                fringes.insert(w.id, w.capacity);
                daddy[w.id] = v.id;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Elapsed time in milliseconds: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    if (status[DESTINATION] != IN_TREE) {
        std::cout << "No path from " << SOURCE << " to " << DESTINATION << std::endl;
        std::cout << "That's impossible! Something is wrong." << std::endl;
        return;
    } else {
        int bw = INFINITY;
        int x = DESTINATION;
        std::stack<int> path;

        path.push(x);
        if (bandwidth[x] < bw && bandwidth[x] != -1) {
            bw = bandwidth[x];
        }
        while (x != SOURCE) {
            x = daddy[x];
            path.push(x);

            if (bandwidth[x] < bw && bandwidth[x] != -1) {
                bw = bandwidth[x];
            }
        }

        while (!path.empty()) {
            x = path.top();
            path.pop();

            if (!path.empty()) {
                std::cout << x << " -> ";
            } else {
                std::cout << x << " with " << bw << " bandwidth" << std::endl;
            }
        }
    }
}

void Algorithms::Kruskal(std::queue<Vertex> *adjacency_list, int n_edges) {
    auto start = std::chrono::high_resolution_clock::now();
    DisjointSet disjointSet;
    EdgeHeap edges_heap(n_edges);

    BFS(adjacency_list, edges_heap);

    if (edges_heap.size() != n_edges) {
        std::cout << "Something is wrong." << std::endl;
        exit(-1);
    }

    std::queue<Vertex> tree[N];
    for (int i = edges_heap.size(); i > 0; --i) {
        Edge edge = edges_heap.get();

        int rank_v = disjointSet.find(edge.vertex_1);
        int rank_w = disjointSet.find(edge.vertex_2);

        if (rank_v != rank_w) {
            disjointSet.join(rank_v, rank_w);

            Vertex vertex;
            vertex.capacity = edge.capacity;

            vertex.id = edge.vertex_2;
            tree[edge.vertex_1].push(vertex);

            vertex.id = edge.vertex_1;
            tree[edge.vertex_2].push(vertex);
        }
    }

    // BFS
    int daddy[N];
    int color[N];
    int bandwidth[N];
    for (int v = 0; v < N; ++v) {
        daddy[v] = -1;
        bandwidth[v] = -1;
        color[v] = WHITE;
    }

    int v = SOURCE;
    color[v] = BLACK;
    bool found = false;

    std::queue<int> queue;
    queue.push(v);

    while (!queue.empty()) {
        v = queue.front();
        queue.pop();

        std::queue<Vertex> temp_queue = tree[v];
        for (unsigned long i = temp_queue.size(); i > 0; --i) {
            Vertex w = temp_queue.front();
            temp_queue.pop();

            if (color[w.id] == WHITE) {
                daddy[w.id] = v;
                bandwidth[w.id] = w.capacity;

                queue.push(w.id);
                color[w.id] = BLACK;
            }

            if (w.id == DESTINATION) {
                found = true;
                break;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Elapsed time in milliseconds: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    if (!found) {
        std::cout << "No path from " << SOURCE << " to " << DESTINATION << std::endl;
        std::cout << "That's impossible! Something is wrong." << std::endl;
        return;
    } else {
        int bw = INFINITY;
        int x = DESTINATION;
        std::stack<int> path;

        path.push(x);
        while (x != SOURCE) {
            x = daddy[x];
            path.push(x);
        }

        while (!path.empty()) {
            x = path.top();
            path.pop();

            if (bw > bandwidth[x] && bandwidth[x] != -1)
                bw = bandwidth[x];

            if (!path.empty()) {
                std::cout << x << " -> ";
            } else {
                std::cout << x << " with " << bw << " bandwidth" << std::endl;
            }
        }
    }
}
