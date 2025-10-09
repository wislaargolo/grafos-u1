#include "CheckBipartite.h"
#include "GraphIO.h"

#include <iostream>
#include <string>

int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    if (is_graph_bipartite(graph)) {
      std::cout << "The graph is bipartite.\n";
    } else {
      std::cout << "The graph is not bipartite.\n";
    }

    return 0;
}
