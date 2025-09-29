#include "GraphAlgorithms.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    auto is_connected = is_connected(graph);
    std::cout << "The graph is " << (is_connected ? "connected." : "not connected.") << "\n";

    return 0;
}