#include "Dfs.h"
#include "GraphIO.h"

#include <iostream>
#include <string>

std::string dfs_edge_type_to_string(EdgeType type) {
    switch (type) {
        case EdgeType::TREE: return "Tree";
        case EdgeType::BACK: return "Back";
        case EdgeType::FORWARD: return "Forward";
        case EdgeType::CROSS: return "Cross";
        default: return "Unknown";
    }
}

int main() {
    std::cout << "Creating graph from file 'DIGRAFO_0.txt'...\n";
    DirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/DIGRAFO_0.txt", graph);
    graph.print();

    auto dfs_result = dfs(graph);
    std::cout << "Result:\n";
    for (const auto& [node, time] : dfs_result.discovery) {
        std::cout << "Node: " << node << ", Discovery Time: " << time 
                  << ", Exit Time: " << dfs_result.exit.at(node) << "\n";
    }
    std::cout << "Edges:\n";
    for (const auto& [type, edges] : dfs_result.edges) {
        std::cout << "  " << dfs_edge_type_to_string(type) << " Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "    " << edge.from << " -> " << edge.to << "\n";
        }
    }

    std::cout << "Creating graph from file 'DIGRAFO1.txt'...\n";
    DirectedAdjacencyListGraph<int> graph1;    
    populate_graph_from_file("data/DIGRAFO1.txt", graph1);
    graph1.print();

    auto dfs_result1 = dfs(graph1);
    std::cout << "Result:\n";
    for (const auto& [node, time] : dfs_result1.discovery) {
        std::cout << "Node: " << node << ", Discovery Time: " << time 
                  << ", Exit Time: " << dfs_result1.exit.at(node) << "\n";
    }
    std::cout << "Edges:\n";
    for (const auto& [type, edges] : dfs_result1.edges) {
        std::cout << "  " << dfs_edge_type_to_string(type) << " Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "    " << edge.from << " -> " << edge.to << "\n";
        }
    }
    return 0;
}