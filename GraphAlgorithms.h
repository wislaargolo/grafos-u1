#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include "graph/UndirectedAdjacencyListGraph.h"
#include "Bfs.h"

template<typename Node>
bool is_connected(const IGraph<Node>& graph) {
    if (graph.get_order() <= 1) return true;

    std::vector<Node> visited = bfs(graph, graph.get_nodes().front());
    return visited.size() == graph.get_order();
}

template<typename Node>
void copy_graph(const IGraph<Node>& from, IGraph<Node>& to) {
    for (Node node : from.get_nodes()) {
        to.add_node(node);

        for (Node neighbor : from.get_neighbors(node)) {
            to.add_edge(node, neighbor);
        }
    }
}

#endif
