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

#endif