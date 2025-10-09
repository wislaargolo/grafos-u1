
#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>
#include <string>

int main() {
    //Tamanho do grafo usando lista de adjacências
    //cria grafo usando lista de adjacencia e printa o grafo
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency list...\n";
    UndirectedAdjacencyListGraph<char> UALGraph;
    populate_graph_from_file("data/GRAFO_0.txt", UALGraph);
    UALGraph.print();
    //printa o tamanho do grafo
    std::cout << "Graph size: " << UALGraph.get_size() << std::endl;

    //Tamanho do grafo usando matriz de adjacências
    //cria grafo usando matriz de adjacencia e printa o grafo
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency matrix...\n";
    UndirectedAdjacencyMatrixGraph<char> UAMGraph;
    populate_graph_from_file("data/GRAFO_0.txt", UAMGraph);
    UAMGraph.print();
    //printa o tamanho do grafo
    std::cout << "Graph size: " << UAMGraph.get_size() << std::endl;

    //Tamanho do digrafo usando lista de adjacências
    //cria digrafo usando lista de adjacencia e printa o digrafo
    std::cout << "Creating graph from file 'DIGRAFO_0.txt' to adjacency list...\n";
    DirectedAdjacencyListGraph<char> DALGraph;
    populate_graph_from_file("data/DIGRAFO_0.txt", DALGraph);
    DALGraph.print();
    //printa o tamanho do digrafo
    std::cout << "Digraph size: " << DALGraph.get_size() << std::endl;

    //Tamanho do digrafo usando matriz de adjacências
    //cria digrafo usando matriz de adjacencia e printa o digrafo
    std::cout << "Creating graph from file 'DIGRAFO_0.txt' to adjacency matrix...\n";
    DirectedAdjacencyMatrixGraph<char> DAMGraph;
    populate_graph_from_file("data/DIGRAFO_0.txt", DAMGraph);
    DAMGraph.print();
    //printa o tamanho do digrafo
    std::cout << "Digraph size: " << DAMGraph.get_size() << std::endl;

    
    return 0;
}

