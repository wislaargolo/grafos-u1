#include "../GraphAlgorithms.h"
#include "../GraphIO.h"

#include <iostream>
#include <string>


int main() {
    //Cria grafo subjacente a partir de um grafo direcionado usando Lista de Adjacências
    std::cout << "Creating graph from file 'DIGRAFO_0.txt'...\n";
    DirectedAdjacencyListGraph<char> directedgraph;
    populate_graph_from_file("data/DIGRAFO_0.txt", directedgraph);
    directedgraph.print();

    std::cout << "Creating subjacent graph by copying directed graph to undirected graph...\n";
    UndirectedAdjacencyListGraph<char> undirected_graph;
    copy_graph(directedgraph, undirected_graph);
    undirected_graph.print();

    //Cria grafo subjacente a partir de um grafo direcionado usando Matriz de Adjacências
    std::cout << "Creating graph from file 'DIGRAFO_0.txt'...\n";
    DirectedAdjacencyMatrixGraph<char> directedgraph_matrix;
    populate_graph_from_file("data/DIGRAFO_0.txt", directedgraph_matrix);
    directedgraph_matrix.print();

    std::cout << "Creating subjacent graph by copying directed graph to undirected graph...\n";
    UndirectedAdjacencyMatrixGraph<char> undirected_graph_matrix;
    copy_graph(directedgraph_matrix, undirected_graph_matrix);
    undirected_graph_matrix.print();


    return 0;
}
