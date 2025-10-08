#ifndef CHECK_BIPARTITION_H
#define CHECK_BIPARTITION_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "graph/IGraph.h"

template<typename Node>
bool check_bipartite_dfs(const IGraph<Node>& graph, std::vector<int>& discovery, int node) {
    for (int neighbor_index : graph.get_neighbors_indices(node)) {
        if (discovery[neighbor_index] == -1) {
            discovery[neighbor_index] = 1 - discovery[node];

            if (!check_bipartite_dfs(graph, discovery, neighbor_index)) {
                return false;
            }
        } else if (discovery[node] == discovery[neighbor_index]) {
            return false;
        }
    }

    return true;
}

template<typename Node>
bool is_graph_bipartite(const IGraph<Node>& graph) {
    size_t size = graph.get_nodes().size();

    if (size == 0) {
        throw std::invalid_argument("Graph is empty");
    }

    std::vector<int> discovery(size, -1);

    for (int i = 0; i < size; i++) {
        if (discovery[i] == -1) {
            discovery[i] = 0;

            if (!check_bipartite_dfs(graph, discovery, i)) {
                return false;
            }
        }
    }

    return true;
}

#endif
