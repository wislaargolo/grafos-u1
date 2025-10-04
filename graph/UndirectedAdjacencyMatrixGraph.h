#ifndef UNDIRECTEDADJACENCYMATRIXGRAPH_H
#define UNDIRECTEDADJACENCYMATRIXGRAPH_H

#include "DirectedAdjacencyMatrixGraph.h"

template<typename Node>
class UndirectedAdjacencyMatrixGraph : public DirectedAdjacencyMatrixGraph<Node> {
public:

    size_t get_size() const override {
        return DirectedAdjacencyMatrixGraph<Node>::get_size() / 2;
    }

    void add_edge(const Node& from, const Node& to) override {
        DirectedAdjacencyMatrixGraph<Node>::add_edge(from, to);
        DirectedAdjacencyMatrixGraph<Node>::add_edge(to, from);
    }

    void remove_edge(const Node& from, const Node& to) override {
        DirectedAdjacencyMatrixGraph<Node>::remove_edge(from, to);
        DirectedAdjacencyMatrixGraph<Node>::remove_edge(to, from);
    }

    void print() const override {
        std::cout  << "Graph (undirected, order: " << this->get_order()
                   << ", size: " << this->get_size() << "):\n";

        if (this->get_order() == 0) {
            std::cout << "(Graph is empty)\n\n";
            return;
        }

        std::cout << "\nAdjacency Matrix:\n";
        std::cout << "    ";

        auto nodes = this->get_nodes();
        for (const auto& node : nodes) {
            std::cout << node << " ";
        }
        std::cout << "\n----";
        for (size_t i = 0; i < this->get_order(); ++i) {
            std::cout << "--";
        }
        std::cout << "\n";

        for (const auto& node_from : nodes) {
            std::cout << node_from << " | ";
            auto neighbors = this->get_neighbors(node_from);
            for (const auto& node_to : nodes) {
                bool is_neighbor = false;
                for(const auto& n : neighbors) {
                    if (n == node_to) {
                        is_neighbor = true;
                        break;
                    }
                }
                if (is_neighbor) {
                    std::cout << "\033[1;32m" << 1 << "\033[0m ";
                } else {
                    std::cout << 0 << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
};

#endif
