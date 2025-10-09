
#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    std::cout << "Creating graph from file 'GRAFO_1.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph1;
    populate_graph_from_file("data/GRAFO_1.txt", graph1);
    graph1.print();

    std::cout << "Creating graph from file 'GRAFO_2.txt'...\n";
    UndirectedAdjacencyListGraph<int> graph2;
    populate_graph_from_file("data/GRAFO_2.txt", graph2);
    graph2.print();

    std::cout << "Creating graph from file 'GRAFO_3.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph3;
    populate_graph_from_file("data/GRAFO_3.txt", graph3);
    graph3.print();

    std::cout << "Creating graph from file 'DIGRAFO_0.txt'...\n";
    DirectedAdjacencyListGraph<char> digraph0;
    populate_graph_from_file("data/DIGRAFO_0.txt", digraph0);
    digraph0.print();
    
    return 0;
}
