#include "Bfs.h"
#include "GraphIO.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "Creating graph from file 'DIGRAFO_0.txt'...\n";
    DirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/DIGRAFO_0.txt", graph);
    graph.print();

    auto bfs_result = bfs_digraph(graph);

    std::cout << "BFS components in the directed graph:\n";
    for (size_t i = 0; i < bfs_result.size(); ++i) {
        std::cout << "Component " << i + 1 << ": ";
        for (const auto& node : bfs_result[i]) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Creating graph from file 'DIGRAFO_1.txt'...\n";
    DirectedAdjacencyListGraph<int> graph1;
    populate_graph_from_file("data/DIGRAFO1.txt", graph1);
    graph1.print();

    auto bfs_result1 = bfs_digraph(graph1);
    std::cout << "BFS components in the directed graph:\n";
    for (size_t i = 0; i < bfs_result1.size(); ++i) {
        std::cout << "Component " << i + 1 << ": ";
        for (const auto& node : bfs_result1[i]) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }
    return 0;
}