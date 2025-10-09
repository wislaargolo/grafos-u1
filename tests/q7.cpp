
#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    std::cout << "Total quantity of nodes: " << graph.get_order() << std::endl;

    std::cout << "Creating graph from file 'GRAFO_1.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph1;
    populate_graph_from_file("data/GRAFO_1.txt", graph1);
    std::cout << "Total quantity of nodes: " << graph1.get_order() << std::endl;

    std::cout << "Creating graph from file 'GRAFO_2.txt'...\n";
    UndirectedAdjacencyListGraph<int> graph2;
    populate_graph_from_file("data/GRAFO_2.txt", graph2);
    std::cout << "Total quantity of nodes: " << graph2.get_order() << std::endl;
    
    std::cout << "Creating graph from file 'GRAFO_3.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph3;
    populate_graph_from_file("data/GRAFO_3.txt", graph3);
    std::cout << "Total quantity of nodes: " << graph3.get_order() << std::endl;
    return 0;
}