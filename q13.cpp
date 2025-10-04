#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    auto bfs_result = bfs(graph, 'a');
    std::cout << "BFS starting from 'a': ";
    for (const auto& node : bfs_result) {
        std::cout << node << " ";
    }
    std::cout << "\n";

    std::cout << "Creating graph from file 'GRAFO_1.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph1;
    populate_graph_from_file("data/GRAFO_1.txt", graph1);
    graph1.print();
    bfs_result = bfs(graph1, graph1.get_nodes().front());
    std::cout << "BFS starting from '" << graph1.get_nodes().front() << "': ";
    for (const auto& node : bfs_result) {
        std::cout << node << " ";
    }
    std::cout << "\n";

    return 0;
}
