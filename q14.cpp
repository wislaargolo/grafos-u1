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
    std::cout << "Result:\n";
    for (const auto& [node, time] : dfs_result.discovery) {
        std::cout << "Node: " << node << ", Discovery Time: " << time 
                  << ", Exit Time: " << dfs_result.exit.at(node) << "\n";
    }
    std::cout << "Edges:\n";
    for (const auto& [type, edges] : dfs_result.edges) {
        std::cout << "  " << type << " Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "    " << edge.from << " -> " << edge.to << "\n";
        }
    }
    return 0;
}