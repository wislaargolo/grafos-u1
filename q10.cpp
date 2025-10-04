
#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>
#include <string>

int main() {

    //Remove no em Lista de Adjacências
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency list...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();
    std::string newNodeStr = "f";
    std::cout << "Removing node: " << newNodeStr << std::endl;
    remove_node_from_string(newNodeStr,graph);
    graph.print();

    //TODO: Remove no em Matriz de Adjacências

    return 0;
}

