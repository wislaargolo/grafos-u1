#ifndef DIRECTEDINCIDENCEMATRIXGRAPH_H
#define DIRECTEDINCIDENCEMATRIXGRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include "IGraph.h"

template<typename Node>
class DirectedIncidenceMatrixGraph : public IGraph<Node> {
protected:
    std::vector<std::vector<int>> matrix;
    std::map<Node, size_t> node_to_index;
    std::map<size_t, Node> index_to_node;

public:
    DirectedIncidenceMatrixGraph() = default;

    size_t get_order() const override { return node_to_index.size(); }
    size_t get_size() const override { return matrix.size(); }

    bool has_node(const Node& node) const override {
        return node_to_index.find(node) != node_to_index.end();
    }

    void add_node(const Node& node) override {
        if (!has_node(node)) {
            size_t index = this->get_order();
            node_to_index[node] = index;
            index_to_node[index] = node;
            for (auto& edge_row : matrix) {
                edge_row.push_back(0);
            }
        }
    }

    void add_edge(const Node& from, const Node& to) override {
        if (!has_node(from)) this->add_node(from);
        if (!has_node(to)) this->add_node(to);

        size_t source_index = node_to_index[from];
        size_t dest_index = node_to_index[to];

        std::vector<int> new_edge(get_order(), 0);
        new_edge[source_index] = -1;
        new_edge[dest_index] = 1;

        matrix.push_back(new_edge);
    }

    std::vector<Node> get_nodes() const override {
        std::vector<Node> nodes;
        nodes.reserve(this->get_order());
        for(size_t i = 0; i < this->get_order(); ++i) {
            nodes.push_back(index_to_node.at(i));
        }
        return nodes;
    }

    int get_index(const Node& node) const override {
        if (has_node(node)) {
            return node_to_index.at(node);
        }
        return -1;
    }

    Node get_node(int index) const override {
        if (index_to_node.count(index)) {
            return index_to_node.at(index);
        }
        throw std::out_of_range("Indice fora do intervalo.");
    }

    std::vector<Node> get_neighbors(const Node& node) const override {
        std::vector<Node> neighbors;
        if (!has_node(node)) return neighbors;

        auto indices = get_neighbors_indices(get_index(node));
        for(int index : indices) {
            neighbors.push_back(get_node(index));
        }
        return neighbors;
    }

    std::vector<int> get_neighbors_indices(int node_index) const override {
        std::vector<int> neighbors_indices;
        if (node_index < 0 || node_index >= static_cast<int>(this->get_order())) return neighbors_indices;

        for (const auto& edge_row : matrix) {
            if (edge_row[node_index] == -1) {
                for (size_t i = 0; i < this->get_order(); ++i) {
                    if (edge_row[i] == 1) {
                        neighbors_indices.push_back(i);
                        break;
                    }
                }
            }
        }
        return neighbors_indices;
    }

    void remove_node(const Node& node) override {
        if (!has_node(node)) return;

        size_t index_to_remove = get_index(node);

        matrix.erase(std::remove_if(matrix.begin(), matrix.end(),
            [index_to_remove](const std::vector<int>& edge_row) {
                return edge_row[index_to_remove] != 0;
            }), matrix.end());

        for (auto& edge_row : matrix) {
            edge_row.erase(edge_row.begin() + index_to_remove);
        }

        index_to_node.erase(index_to_remove);
        node_to_index.erase(node);

        for (size_t i = index_to_remove; i < get_order(); ++i) {
            Node n = index_to_node.at(i + 1);
            index_to_node[i] = n;
            node_to_index[n] = i;
        }
        index_to_node.erase(get_order());
    }

    void remove_edge(const Node& from, const Node& to) override {
        if (!has_node(from) || !has_node(to)) return;

        size_t from_index = get_index(from);
        size_t to_index = get_index(to);
        matrix.erase(std::remove_if(matrix.begin(), matrix.end(),
            [from_index, to_index](const std::vector<int>& edge_row) {
                return edge_row[from_index] == -1 && edge_row[to_index] == 1;
            }), matrix.end());
    }

    void print() const override {
        std::cout << "Grafo (direcionado, ordem: " << this->get_order()
                  << ", tamanho: " << this->get_size() << "):\n";
        if (this->get_order() == 0) {
            std::cout << "(Grafo esta vazio)\n\n";
            return;
        }
        std::cout << "\nMatriz de Incidencia (Arestas x Vertices):\n";

        std::cout << "    |";
        for (size_t i = 0; i < this->get_order(); ++i) {
            std::cout << " " << index_to_node.at(i) << " ";
        }
        std::cout << "\n----|";
        for (size_t i = 0; i < this->get_order(); ++i) {
            std::cout << "---";
        }
        std::cout << "\n";

        for (size_t i = 0; i < this->get_size(); ++i) {
            std::cout << " a" << i + 1 << " |";
            for (size_t j = 0; j < this->get_order(); ++j) {
                int value = matrix[i][j];
                 if (value == 1) {
                    std::cout << "\033[1;32m" << "+" << value << "\033[0m "; // Verde para chegada
                } else if (value == -1) {
                    std::cout << "\033[1;31m" << value << "\033[0m "; // Vermelho para saída
                } else {
                    std::cout << " " << value << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    size_t get_in_degree(const Node& node) const override {
        if (!has_node(node)) {
            return 0;
        }
        size_t node_idx = node_to_index.at(node);
        size_t in_degree = 0;
        for (const auto& edge_row : matrix) {
            if (edge_row[node_idx] == 1) {
                in_degree++;
            }
        }
        return in_degree;
    }

    size_t get_out_degree(const Node& node) const override {
        if (!has_node(node)) {
            return 0;
        }
        size_t node_idx = node_to_index.at(node);
        size_t out_degree = 0;
        for (const auto& edge_row : matrix) {
            if (edge_row[node_idx] == -1) {
                out_degree++;
            }
        }
        return out_degree;
    }

    bool is_adjacent(const Node& u, const Node& v) const override {
        int u_idx = get_index(u);
        int v_idx = get_index(v);
        for (const auto& edge_row : matrix) {
            if (edge_row[u_idx] == -1 && edge_row[v_idx] == 1) {
                return true;
            }
        }
        return false;
    }
};

#endif
