#include "../GraphAlgorithms.h"

#include <iostream>
#include <string>
#include "../GraphIO.h"
#include "../graph/DirectedIncidenceMatrixGraph.h"


int main() {
    std::cout << "Creating graph from file 'DIGRAFO_0.txt'...\n";
    DirectedIncidenceMatrixGraph<char> graph;
    populate_graph_from_file("data/DIGRAFO_0.txt", graph);
    graph.print();

    std::cout << "Creating graph from file 'DIGRAFO_1.txt'...\n";
    // A CORREÇÃO ESTÁ AQUI: Mude de 'char' para 'int'
    DirectedIncidenceMatrixGraph<char> graph1;
    populate_graph_from_file("data/DIGRAFO_1.txt", graph1);
    graph1.print();

    std::cout << "Creating graph from file 'DIGRAFO_2.txt'...\n";
    DirectedIncidenceMatrixGraph<char> graph2;
    populate_graph_from_file("data/DIGRAFO_2.txt", graph2);
    graph2.print();

    std::cout << "Creating graph from file 'DIGRAFO_3.txt'...\n";
    DirectedIncidenceMatrixGraph<char> graph3;
    populate_graph_from_file("data/DIGRAFO_3.txt", graph3);
    graph3.print();

    return 0;
}
