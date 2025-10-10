#include <iostream>
#include "../GraphIO.h"
#include "../graph/DirectedAdjacencyListGraph.h"
#include "../graph/DirectedAdjacencyMatrixGraph.h"
#include "../graph/DirectedIncidenceMatrixGraph.h"
#include "../graph/UndirectedAdjacencyListGraph.h"
#include "../graph/UndirectedAdjacencyMatrixGraph.h"
#include "../graph/UndirectedIncidenceMatrixGraph.h"

template<typename GraphType>
void print_degree(const std::string& graph_name, const std::string& filename) {
    GraphType graph;
    populate_graph_from_file(filename, graph);
    graph.print();

    std::cout << "Calculando graus dos vertices:\n";
    for (const auto& node : graph.get_nodes()) {
        std::cout << "  Vertice " << node << ": "
                  << "Grau de Entrada (in-degree): " << graph.get_in_degree(node)
                  << ", Grau de Saida (out-degree): " << graph.get_out_degree(node)
                  << std::endl;
    }
    std::cout << "\n";
}

int main() {
    const std::string digrafo_file = "data/DIGRAFO_0.txt";
    print_degree<DirectedAdjacencyListGraph<char>>("Directed Adjacency List", digrafo_file);
    print_degree<DirectedAdjacencyMatrixGraph<char>>("Directed Adjacency Matrix", digrafo_file);
    print_degree<DirectedIncidenceMatrixGraph<char>>("Directed Incidence Matrix", digrafo_file);

    const std::string grafo_file = "data/GRAFO_0.txt";
    print_degree<UndirectedAdjacencyListGraph<char>>("Undirected Adjacency List", grafo_file);
    print_degree<UndirectedAdjacencyMatrixGraph<char>>("Undirected Adjacency Matrix", grafo_file);
    print_degree<UndirectedIncidenceMatrixGraph<char>>("Undirected Incidence Matrix", grafo_file);

    return 0;
}
