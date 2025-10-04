#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "Dfs.h"
#include "graph/UndirectedAdjacencyListGraph.h"

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
void add_node_from_string(const std::string& str, IGraph<Node>& graph) {
    Node node;
    std::stringstream ss(str);
    ss >> node;
    graph.add_node(node);
} 

template<typename Node>
void remove_node_from_string(const std::string& str, IGraph<Node>& graph) {
    Node node;
    std::stringstream ss(str);
    ss >> node;
    graph.remove_node(node);
} 

std::ostream& operator<<(std::ostream& os, EdgeType type) {
    switch (type) {
        case EdgeType::TREE:    
            os << "Tree";    
            break;
        case EdgeType::BACK:    
            os << "Back";    
            break;
        case EdgeType::FORWARD: 
            os << "Forward"; 
            break;
        case EdgeType::CROSS:   
            os << "Cross";   
            break;
        default:                
            os << "Unknown"; 
            break;
    }
    return os;
}

#endif // GRAPH_IO_H