#include "GraphAlgorithms.h"

#include <iostream>
#include <string>
#include "GraphIO.h"
#include "graph/AdjacencyMatrixGraph.h"


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    AdjacencyMatrixGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    std::cout << "Creating graph from file 'GRAFO_1.txt'...\n";
    AdjacencyMatrixGraph<char> graph1;
    populate_graph_from_file("data/GRAFO_1.txt", graph1);
    graph1.print();

    std::cout << "Creating graph from file 'GRAFO_2.txt'...\n";
    AdjacencyMatrixGraph<int> graph2;
    populate_graph_from_file("data/GRAFO_2.txt", graph2);
    graph2.print();

    std::cout << "Creating graph from file 'GRAFO_3.txt'...\n";
    AdjacencyMatrixGraph<char> graph3;
    populate_graph_from_file("data/GRAFO_3.txt", graph3);
    graph3.print();

    // true indicates directed graph
    std::cout << "Creating graph from file 'DIGRAFO_0.txt'...\n";
    AdjacencyMatrixGraph<char> graph4(true);
    populate_graph_from_file("data/DIGRAFO_0.txt", graph4);
    graph4.print();

    std::cout << "Creating graph from file 'DIGRAFO1.txt'...\n";
    AdjacencyMatrixGraph<int> graph5(true);
    populate_graph_from_file("data/DIGRAFO1.txt", graph5);
    graph5.print();

    std::cout << "Creating graph from file 'DIGRAFO2.txt'...\n";
    AdjacencyMatrixGraph<int> graph6(true);
    populate_graph_from_file("data/DIGRAFO2.txt", graph6);
    graph6.print();

    std::cout << "Creating graph from file 'DIGRAFO3.txt'...\n";
    AdjacencyMatrixGraph<char> graph7(true);
    populate_graph_from_file("data/DIGRAFO3.txt", graph7);
    graph7.print();

    return 0;
}
