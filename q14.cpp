#include "Dfs.h"
#include "GraphIO.h"

#include <iostream>
#include <string>

int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    auto dfs_result = dfs_unidirectional(graph, graph.get_nodes().front());
    std::cout << "DFS starting from : " << graph.get_nodes().front() << "\n";
    std::cout << "Result: ";
    for (const auto& node : dfs_order(dfs_result)) {
        std::cout << node << " ";
    }
    std::cout << "\nBack edges:\n";
    for (const auto& [from, to] : dfs_result.edges[EdgeType::BACK]) {
        std::cout << from << " - " << to << "\n";
    }

    std::cout << "DFS tree edges:\n";
    for( const auto& [from, to] : dfs_result.parent) {
        std::cout << to << " - " << from << "\n";
    }
}