#ifndef DIRECTEDADJACENCYMATRIXGRAPH_H
#define DIRECTEDADJACENCYMATRIXGRAPH_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

#include "IGraph.h"

template<typename Node>
class DirectedAdjacencyMatrixGraph : public IGraph<Node> {
private:
    std::vector<std::vector<int>> matrix;
    std::vector<Node> index_to_node;
    std::unordered_map<Node, size_t> node_to_index;

public:
    explicit DirectedAdjacencyMatrixGraph() = default;

    explicit DirectedAdjacencyMatrixGraph(const std::vector<Node>& initial_nodes) {
        for (const auto& node : initial_nodes) {
            add_node(node);
        }
    }

    size_t get_order() const override {
        return index_to_node.size();
    }

    size_t get_size() const override {
        size_t edge_count = 0;
        for (const auto& row : matrix) {
            for (int val : row) {
                if (val == 1) {
                    edge_count++;
                }
            }
        }
        return edge_count;
    }

    bool has_node(const Node& node) const override {
        return node_to_index.count(node) > 0;
    }

    void add_node(const Node& node) override {
        if (has_node(node)) {
            return;
        }

        size_t new_index = get_order();
        node_to_index[node] = new_index;
        index_to_node.push_back(node);

        matrix.push_back(std::vector<int>(get_order(), 0));

        for (auto& row : matrix) {
            row.resize(get_order(), 0);
        }
    }

    void remove_node(const Node& node) override {
        if (!has_node(node)) {
            throw std::runtime_error("Cannot remove node: node does not exist.");
        }

        size_t index_to_remove = node_to_index.at(node);
        size_t last_index = get_order() - 1;

        if (index_to_remove != last_index) {
            std::swap(matrix[index_to_remove], matrix[last_index]);
            for (size_t i = 0; i < get_order(); ++i) {
                std::swap(matrix[i][index_to_remove], matrix[i][last_index]);
            }
        }

        matrix.pop_back();
        for (auto& row : matrix) {
            row.pop_back();
        }

        Node last_node = index_to_node.back();
        node_to_index.erase(node);
        index_to_node.erase(index_to_node.begin() + index_to_remove);

        if (index_to_remove != last_index) {
            index_to_node[index_to_remove] = last_node;
            node_to_index[last_node] = index_to_remove;
        }
    }

    void add_edge(const Node& from, const Node& to) override {
        if (!has_node(from)) add_node(from);
        if (!has_node(to)) add_node(to);

        size_t from_idx = node_to_index.at(from);
        size_t to_idx = node_to_index.at(to);

        matrix[from_idx][to_idx] = 1;
    }

    void remove_edge(const Node& from, const Node& to) override {
        if (has_node(from) && has_node(to)) {
            size_t from_idx = node_to_index.at(from);
            size_t to_idx = node_to_index.at(to);
            matrix[from_idx][to_idx] = 0;
        }
    }

    std::vector<Node> get_neighbors(const Node& node) const override {
        if (!has_node(node)) {
            return {};
        }

        size_t node_idx = node_to_index.at(node);
        std::vector<Node> neighbors;
        for (size_t j = 0; j < get_order(); ++j) {
            if (matrix[node_idx][j] == 1) {
                neighbors.push_back(index_to_node[j]);
            }
        }
        return neighbors;
    }

    std::vector<Node> get_nodes() const override {
        return index_to_node;
    }

    void print() const override {
        std::cout  << "Graph (directed, order: " << get_order()
                   << ", size: " << get_size() << "):\n";

        if (get_order() == 0) {
            std::cout << "(Graph is empty)\n\n";
            return;
        }

        std::cout << "\nAdjacency Matrix:\n";
        std::cout << "    ";
        for (const auto& node : index_to_node) {
            std::cout << node << " ";
        }
        std::cout << "\n----";
        for (size_t i = 0; i < get_order(); ++i) {
            std::cout << "--";
        }
        std::cout << "\n";

        for (size_t i = 0; i < get_order(); ++i) {
            std::cout << index_to_node[i] << " | ";
            for (size_t j = 0; j < get_order(); ++j) {
                if (matrix[i][j] == 1) {
                    std::cout << "\033[1;32m" << matrix[i][j] << "\033[0m ";
                } else {
                    std::cout << matrix[i][j] << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
};

#endif
