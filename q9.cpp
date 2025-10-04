
#include "GraphAlgorithms.h"
#include "GraphIO.h"
#include "graph/IGraph.h"

#include <iostream>
#include <string>
#include <string>

int main() {

    //Aciona no em Lista de Adjacências
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency list...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();
    std::string newNodeStr = "x";
    std::cout << "Adding node: " << newNodeStr << std::endl;
    add_node_from_string(newNodeStr,graph);
    graph.print();

    //TODO: Adiciona no em Matriz de Adjacências

    return 0;
}

