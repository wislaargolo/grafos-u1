#include "Dfs.h"
#include "GraphIO.h"

#include <iostream>
#include <string>

int main() {
    std::cout << "Creating graph from file 'DIGRAFO_0.txt'...\n";
    DirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/DIGRAFO_0.txt", graph);
    graph.print();

    auto dfs_result = dfs(graph);
    std::cout << "Result: ";
    for (const auto& node : dfs_order(dfs_result)) {
        std::cout << node << " ";
    }
    std::cout << "\nEdges by type:\n";
    for (const auto& [type, edges] : dfs_result.edges) {
        std::string type_str;
        switch (type) {
            case EdgeType::TREE: type_str = "Tree"; break;
            case EdgeType::BACK: type_str = "Back"; break;
            case EdgeType::FORWARD: type_str = "Forward"; break;
            case EdgeType::CROSS: type_str = "Cross"; break;
        }
        std::cout << type_str << " edges:\n";
        for (const auto& [from, to] : edges) {
            std::cout << from << " - " << to << "\n";
        }
    }
    std::cout << "DFS tree edges:\n";
    for( const auto& [from, to] : dfs_result.parent) {
        std::cout << to << " - " << from << "\n";
    }
}