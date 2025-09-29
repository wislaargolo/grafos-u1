#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include "UndirectedAdjacencyListGraph.h"

template<typename Node>
void populate_graph_from_file(const std::string& filename, IGraph<Node>& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::getline(file, line); // Skip the first line 

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        Node u, v; 
        char comma;
        
        if (ss >> u >> comma >> v) {
            graph.add_edge(u, v);
        }
    }
    file.close();
}


template<typename Node>
std::vector<Node> bfs(const IGraph<Node>& graph, Node start) {
    std::vector<Node> visited;
    std::queue<Node> queue;

    if (!graph.has_node(start)) {
        std::cerr << "Start node '" << start << "' does not exist in the graph.\n";
        return visited; 
    }

    visited.push_back(start);
    queue.push(start);

    while (!queue.empty()) {
        Node current = queue.front();
        queue.pop();

        for (const auto& neighbor : graph.get_neighbors(current)) {
            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                visited.push_back(neighbor);
                queue.push(neighbor);
            }
        }
    }

    return visited;
}

template<typename Node>
bool is_connected(const IGraph<Node>& graph) {
    if (graph.get_order() <= 1) return true; 

    std::vector<Node> visited = bfs(graph, graph.get_nodes().front());
    return visited.size() == graph.get_order();
}

#endif