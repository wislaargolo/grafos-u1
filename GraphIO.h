#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "Dfs.h"
#include "graph/UndirectedAdjacencyListGraph.h"

/**
 * @brief Popula um grafo com dados de um arquivo de texto.
 * 
 * @details O formato esperado do arquivo é:
 * 1. Uma primeira linha de cabeçalho, que é ignorada.
 * 2. Linhas subsequentes no formato "u,v", onde 'u' e 'v' são os nós
 * que formam uma aresta.
 *
 * @tparam Node O tipo de dado dos nós do grafo.
 * @param filename O caminho para o arquivo de entrada.
 * @param graph O objeto grafo a ser populado.
 * @throws std::runtime_error se o arquivo não puder ser aberto.
 */
template<typename Node>
void populate_graph_from_file(const std::string& filename, IGraph<Node>& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    /*Ignora a primeira linha de cabeçalho*/
    std::getline(file, line); 

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        Node u, v; 
        char comma;
        
        /*Lê os nós u e v separados por vírgula*/
        if (ss >> u >> comma >> v) {
            graph.add_edge(u, v);
        }
    }
    file.close();
}

template<typename Node>
void add_node_from_string(const std::string& str, IGraph<Node>& graph) {
    Node node;
    std::stringstream ss(str);
    ss >> node;
    graph.add_node(node);
} 

template<typename Node>
void remove_node_from_string(const std::string& str, IGraph<Node>& graph) {
    Node node;
    std::stringstream ss(str);
    ss >> node;
    graph.remove_node(node);
} 

std::ostream& operator<<(std::ostream& os, EdgeType type) {
    switch (type) {
        case EdgeType::TREE:    
            os << "Tree";    
            break;
        case EdgeType::BACK:    
            os << "Back";    
            break;
        case EdgeType::FORWARD: 
            os << "Forward"; 
            break;
        case EdgeType::CROSS:   
            os << "Cross";   
            break;
        default:                
            os << "Unknown"; 
            break;
    }
    return os;
}

#endif // GRAPH_IO_H