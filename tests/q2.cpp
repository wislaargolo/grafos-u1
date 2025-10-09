#include "GraphAlgorithms.h"

#include <iostream>
#include <string>
#include "GraphIO.h"
#include "graph/DirectedAdjacencyMatrixGraph.h"
#include "graph/UndirectedAdjacencyMatrixGraph.h"


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyMatrixGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    std::cout << "Creating graph from file 'GRAFO_1.txt'...\n";
    UndirectedAdjacencyMatrixGraph<char> graph1;
    populate_graph_from_file("data/GRAFO_1.txt", graph1);
    graph1.print();

    std::cout << "Creating graph from file 'GRAFO_2.txt'...\n";
    UndirectedAdjacencyMatrixGraph<int> graph2;
    populate_graph_from_file("data/GRAFO_2.txt", graph2);
    graph2.print();

    std::cout << "Creating graph from file 'GRAFO_3.txt'...\n";
    UndirectedAdjacencyMatrixGraph<char> graph3;
    populate_graph_from_file("data/GRAFO_3.txt", graph3);
    graph3.print();

    return 0;
}
