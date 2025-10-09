
#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>
#include <string>

int main() {

    //comum
    std::string newNodeStr = "f";


    //Remover no em Lista de Adjacências
    //cria grafo usando lista de adjacencia e printa o grafo
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency list...\n";
    UndirectedAdjacencyListGraph<char> ALGraph;
    populate_graph_from_file("data/GRAFO_0.txt", ALGraph);
    ALGraph.print();

    //Remove o no f do grafo e printa o gtrafo novamente
    std::cout << "Removing node: " << newNodeStr << std::endl;
    remove_node_from_string(newNodeStr,ALGraph);
    ALGraph.print();


    //Remove no em Matriz de Adjacências
    //cria grafo usando matriz de adjacencia e printa o grafo
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency matrix...\n";
    UndirectedAdjacencyMatrixGraph<char> AMGraph;
    populate_graph_from_file("data/GRAFO_0.txt", AMGraph);
    AMGraph.print();

    //Remove o no f do grafo e printa o gtrafo novamente
    std::cout << "Removing node: " << newNodeStr << std::endl;
    remove_node_from_string(newNodeStr,AMGraph);
    AMGraph.print();

    return 0;
}

