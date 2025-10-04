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
    for (const auto& node : dfs_pre_order(dfs_result)) {
        std::cout << node << " ";
    }
    std::cout << "\nEdges by type:\n";
    for (const auto& [type, edges] : dfs_result.edges) {
        std::cout << type << " edges:\n";
        for (const auto& [from, to] : edges) {
            std::cout << from << " - " << to << "\n";
        }
    }
    std::cout << "DFS tree edges:\n";
    for( const auto& [from, to] : dfs_result.parent) {
        std::cout << to << " - " << from << "\n";
    }
}