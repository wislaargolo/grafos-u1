#include "../DivideBlocks.h"
#include "../GraphIO.h"

#include <iostream>
#include <string>

int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    auto result = divide_blocks(graph);

    std::cout << "Articulations:\n";

    for (char node : result.articulations) {
        std::cout << node << "\n";
    }

    std::cout << "\nBlocks:\n";
    for (const auto& block : result.blocks) {
        for (char node : block) {
            std::cout << node << " ";
        }

        std::cout << "\n";
    }

    return 0;
}
