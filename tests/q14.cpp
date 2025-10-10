#include "Dfs.h"
#include "GraphIO.h"

#include <iostream>
#include <string>

std::string dfs_edge_type_to_string(EdgeType type) {
    switch (type) {
        case EdgeType::TREE: return "Tree";
        case EdgeType::BACK: return "Back";
        case EdgeType::FORWARD: return "Forward";
        case EdgeType::CROSS: return "Cross";
        default: return "Unknown";
    }
}

int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph;
    populate_graph_from_file("data/GRAFO_0.txt", graph);
    graph.print();

    auto dfs_result = dfs_unidirectional(graph, graph.get_nodes().front());
    std::cout << "Result:\n";
    for (const auto& [node, time] : dfs_result.discovery) {
        std::cout << "Node: " << node << ", Discovery Time: " << time 
                  << ", Exit Time: " << dfs_result.exit.at(node) << "\n";
    }
    std::cout << "Edges:\n";
    for (const auto& [type, edges] : dfs_result.edges) {
        std::cout << "  " << dfs_edge_type_to_string(type) << " Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "    " << edge.from << " -> " << edge.to << "\n";
        }
    }

    std::cout << "Creating graph from file 'GRAFO_1.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph1;
    populate_graph_from_file("data/GRAFO_1.txt", graph1);
    graph1.print();

    auto dfs_result1 = dfs_unidirectional(graph1, graph1.get_nodes().front());
    std::cout << "Result:\n";
    for (const auto& [node, time] : dfs_result1.discovery) {
        std::cout << "Node: " << node << ", Discovery Time: " << time
                  << ", Exit Time: " << dfs_result1.exit.at(node) << "\n";
    }
    std::cout << "Edges:\n";
    for (const auto& [type, edges] : dfs_result1.edges) {
        std::cout << "  " << dfs_edge_type_to_string(type) << " Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "    " << edge.from << " -> " << edge.to << "\n";
        }
    }

    std::cout << "Creating graph from file 'GRAFO_2.txt'...\n";
    UndirectedAdjacencyListGraph<int> graph2;   
    populate_graph_from_file("data/GRAFO_2.txt", graph2);
    graph2.print();
    auto dfs_result2 = dfs_unidirectional(graph2, graph2.get_nodes().front());
    std::cout << "Result:\n";
    for (const auto& [node, time] : dfs_result2.discovery) {
        std::cout << "Node: " << node << ", Discovery Time: " << time
                  << ", Exit Time: " << dfs_result2.exit.at(node) << "\n";
    }
    std::cout << "Edges:\n";
    for (const auto& [type, edges] : dfs_result2.edges) {
        std::cout << "  " << dfs_edge_type_to_string(type) << " Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "    " << edge.from << " -> " << edge.to << "\n";
        }
    }   

    std::cout << "\n";
    std::cout << "Creating graph from file 'GRAFO_3.txt'...\n";
    UndirectedAdjacencyListGraph<char> graph3;
    populate_graph_from_file("data/GRAFO_3.txt", graph3);
    graph3.print();

    auto dfs_result3 = dfs_unidirectional(graph3, graph3.get_nodes().front());
    std::cout << "Result:\n";
    for (const auto& [node, time] : dfs_result3.discovery) {
        std::cout << "Node: " << node << ", Discovery Time: " << time
                  << ", Exit Time: " << dfs_result3.exit.at(node) << "\n";
    }
    std::cout << "Edges:\n";
    for (const auto& [type, edges] : dfs_result3.edges) {
        std::cout << "  " << dfs_edge_type_to_string(type) << " Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "    " << edge.from << " -> " << edge.to << "\n";
        }
    }

    return 0;
}