
#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>
#include <string>

int main() {

    //comum
    std::string newNodeStr = "x";

    //Aciona no em Lista de Adjacências
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency list...\n";
    UndirectedAdjacencyListGraph<char> ALGraph;
    populate_graph_from_file("data/GRAFO_0.txt", ALGraph);
    ALGraph.print();
    
    std::cout << "Adding node: " << newNodeStr << std::endl;
    add_node_from_string(newNodeStr,ALGraph);
    ALGraph.print();

    //Adiciona no em Matriz de Adjacências
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency Matrix...\n";
    UndirectedAdjacencyMatrixGraph<char> AMGraph;
    populate_graph_from_file("data/GRAFO_0.txt", AMGraph);
    AMGraph.print();
    std::cout << "Adding node: " << newNodeStr << std::endl;
    add_node_from_string(newNodeStr,AMGraph);
    AMGraph.print();

    return 0;
}

