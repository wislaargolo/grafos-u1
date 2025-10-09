#include "GraphAlgorithms.h"

#include <iostream>
#include <string>
#include "GraphIO.h"
#include "GraphAlgorithms.h"
#include "graph/UndirectedAdjacencyListGraph.h"
#include "graph/UndirectedAdjacencyMatrixGraph.h"


int main() {
    std::cout << "Creating adjacency list graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph0;
    populate_graph_from_file("data/GRAFO_0.txt", graph0);
    graph0.print();

    std::cout << "Converting graph to adjacency matrix...\n";
    UndirectedAdjacencyMatrixGraph<char> graph1;
    copy_graph(graph0, graph1);
    graph1.print();

    std::cout << "Creating adjacency matrix graph from file 'GRAFO_1.txt'...\n";
    UndirectedAdjacencyMatrixGraph<char> graph2;
    populate_graph_from_file("data/GRAFO_1.txt", graph2);
    graph2.print();

    std::cout << "Converting graph to adjacency list...\n";
    UndirectedAdjacencyListGraph<char> graph3;
    copy_graph(graph2, graph3);
    graph3.print();

    return 0;
}
