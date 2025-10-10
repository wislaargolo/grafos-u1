#include "GraphAlgorithms.h"
#include "GraphIO.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    auto bfs_result = bfs(graph, 'a');
    std::cout << "BFS starting from 'a': ";
    for (const auto& node : bfs_result) {
        std::cout << node << " ";
    }
    std::cout << "\n";

    std::cout << "Creating graph from file 'GRAFO_1.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph1;
    populate_graph_from_file("data/GRAFO_1.txt", graph1);
    graph1.print();
    bfs_result = bfs(graph1, graph1.get_nodes().front());
    std::cout << "BFS starting from '" << graph1.get_nodes().front() << "': ";
    for (const auto& node : bfs_result) {
        std::cout << node << " ";
    }
    std::cout << "\n";

    std::cout << "Is connected? " << (is_connected(graph1) ? "Yes" : "No") << "\n";

    std::cout << "Creating graph from file 'GRAFO_2.txt'...\n";
    UndirectedAdjacencyListGraph<int> graph2;  
    populate_graph_from_file("data/GRAFO_2.txt", graph2);
    graph2.print();
    auto bfs_result1 = bfs(graph2, graph2.get_nodes().front());
    std::cout << "BFS starting from '" << graph2.get_nodes().front() << "': ";
    for (const auto& node : bfs_result1) {
        std::cout << node << " ";
    }
    std::cout << "\n";

    std::cout << "Is connected? " << (is_connected(graph2) ? "Yes" : "No") << "\n";

    std::cout << "Creating graph from file 'GRAFO_3.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph3;
    populate_graph_from_file("data/GRAFO_3.txt", graph3);
    graph3.print();     

    bfs_result = bfs(graph3, graph3.get_nodes().front());
    std::cout << "BFS starting from '" << graph3.get_nodes().front() << "': ";
    for (const auto& node : bfs_result) {
        std::cout << node << " ";
    }       

    std::cout << "\n";

    std::cout << "Is connected? " << (is_connected(graph3) ? "Yes" : "No") << "\n";

    return 0;
}
