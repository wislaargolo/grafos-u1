#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    bool connected = is_connected(graph);
    std::cout << "The graph is " << (connected ? "connected." : "not connected.") << "\n";


    std::cout << "Creating graph from file 'GRAFO_1.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph1;
    populate_graph_from_file("data/GRAFO_1.txt", graph1);
    graph1.print();

    connected = is_connected(graph1);
    std::cout << "The graph is " << (connected ? "connected." : "not connected.") << "\n";

    return 0;
}