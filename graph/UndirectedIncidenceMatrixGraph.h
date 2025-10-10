#ifndef UNDIRECTEDINCIDENCEMATRIXGRAPH_H
#define UNDIRECTEDINCIDENCEMATRIXGRAPH_H

#include "DirectedIncidenceMatrixGraph.h" // Inclui a classe pai
#include <vector>
#include <string>

template<typename Node>
class UndirectedIncidenceMatrixGraph : public DirectedIncidenceMatrixGraph<Node> {
public:
    UndirectedIncidenceMatrixGraph() = default;

    void add_edge(const Node& node1, const Node& node2) override {
        if (!this->has_node(node1)) this->add_node(node1);
        if (!this->has_node(node2)) this->add_node(node2);

        size_t index1 = this->node_to_index[node1];
        size_t index2 = this->node_to_index[node2];

        std::vector<int> new_edge(this->get_order(), 0);
        new_edge[index1] = 1;
        new_edge[index2] = 1;

        this->matrix.push_back(new_edge);
    }

    std::vector<int> get_neighbors_indices(int node_index) const override {
        std::vector<int> neighbors_indices;
        if (node_index < 0 || node_index >= static_cast<int>(this->get_order())) return neighbors_indices;

        for (const auto& edge_row : this->matrix) {
            if (edge_row[node_index] == 1) {
                for (size_t i = 0; i < this->get_order(); ++i) {
                    if (i != static_cast<size_t>(node_index) && edge_row[i] == 1) {
                        neighbors_indices.push_back(i);
                        break;
                    }
                }
            }
        }
        return neighbors_indices;
    }

    void remove_edge(const Node& node1, const Node& node2) override {
        if (!this->has_node(node1) || !this->has_node(node2)) return;

        size_t index1 = this->get_index(node1);
        size_t index2 = this->get_index(node2);

        this->matrix.erase(std::remove_if(this->matrix.begin(), this->matrix.end(),
            [index1, index2](const std::vector<int>& edge_row) {
                return edge_row[index1] == 1 && edge_row[index2] == 1;
            }), this->matrix.end());
    }

    void print() const override {
        std::cout << "Grafo (nao direcionado, ordem: " << this->get_order()
                  << ", tamanho: " << this->get_size() << "):\n";
        if (this->get_order() == 0) {
            std::cout << "(Grafo esta vazio)\n\n";
            return;
        }
        std::cout << "\nMatriz de Incidencia (Arestas x Vertices):\n";

        std::cout << "    |";
        for (size_t i = 0; i < this->get_order(); ++i) {
            std::cout << " " << this->index_to_node.at(i) << " ";
        }
        std::cout << "\n----|";
        for (size_t i = 0; i < this->get_order(); ++i) {
            std::cout << "---";
        }
        std::cout << "\n";

        for (size_t i = 0; i < this->get_size(); ++i) {
            std::cout << " a" << i + 1 << " |";
            for (int value : this->matrix[i]) {
                if (value == 1) {
                    std::cout << "\033[1;32m" << " " << value << "\033[0m ";
                } else {
                    std::cout << " " << value << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    size_t get_in_degree(const Node& node) const override {
        if(!this->has_node(node)) return 0;
        size_t node_index = this->get_index(node);
        size_t degree = 0;
        for (const auto& edge_row : this->matrix) {
            if (edge_row[node_index] == 1) {
                degree++;
            }
        }
        return degree;
    }

    size_t get_out_degree(const Node& node) const override {
        return get_in_degree(node);
    }
};

#endif
