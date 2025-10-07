#ifndef DIRECTEDADJACENCYLISTGRAPH_H
#define DIRECTEDADJACENCYLISTGRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> 

#include "IGraph.h"
template<typename Node>
class DirectedAdjacencyListGraph : public IGraph<Node> {
    private:
        std::vector<std::vector<int>> adjac;       
        std::vector<Node> index_to_node;           
        std::unordered_map<Node, size_t> node_to_index; 
    public:

        size_t get_order() const override {
            return index_to_node.size();
        }

        size_t get_size() const override {
            size_t edge_count = 0;
            for(const auto& neighbors : adjac) {
                edge_count += neighbors.size();
            }
            return edge_count;
        }

        void add_node(const Node& node) override {
            auto it = node_to_index.find(node);
            if (it == node_to_index.end()) {
                node_to_index[node] = index_to_node.size();
                index_to_node.push_back(node);
                adjac.emplace_back();
            }
        }

        void remove_node(const Node& node) override {
            auto it = node_to_index.find(node);
            if (it != node_to_index.end()) {
                size_t index = it->second;
                size_t last_index = index_to_node.size() - 1;

                for (auto& neighbors : adjac) {
                    neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), index), neighbors.end());
                }

                if(index != last_index) {
                    Node last_node = index_to_node[last_index];
                    std::swap(index_to_node[index], index_to_node[last_index]);
                    std::swap(adjac[index], adjac[last_index]);
                    node_to_index[last_node] = index;
                }

                for(auto& neighbors : adjac) {
                    for(auto& neighbor_index : neighbors) {
                        if(neighbor_index == static_cast<int>(last_index)) {
                            neighbor_index = index;
                        }
                    }
                }

                index_to_node.pop_back();
                adjac.pop_back();
                node_to_index.erase(it);
        
            }
        }

        void add_edge(const Node& from, const Node& to) override {
            add_node(from);
            add_node(to);
            size_t from_index = node_to_index[from];
            size_t to_index = node_to_index[to];

            auto& neighbors_from = adjac[from_index];
            if (std::find(neighbors_from.begin(), neighbors_from.end(), to_index) == neighbors_from.end()) {
                neighbors_from.push_back(to_index);
            }
        }

        void remove_edge(const Node& from, const Node& to) override {
            auto it_from = node_to_index.find(from);
            auto it_to = node_to_index.find(to);
            if (it_from != node_to_index.end() && it_to != node_to_index.end()) {
                size_t from_index = it_from->second;
                size_t to_index = it_to->second;

                auto& neighbors_from = adjac[from_index];
                neighbors_from.erase(std::remove(neighbors_from.begin(), neighbors_from.end(), to_index), neighbors_from.end());
            }
             
        }

        std::vector<Node> get_neighbors(const Node& node) const override {
            auto it = node_to_index.find(node);
            if (it == node_to_index.end()) {
                return {};
            }

            size_t index = it->second;
            std::vector<Node> neighbors;
            neighbors.reserve(adjac[index].size());
            for (int neighbor_index : adjac[index]) {
                neighbors.push_back(index_to_node[neighbor_index]);
            }
            return neighbors;
        }

        std::vector<int> get_neighbors_indices(int index) const override {
            if (index < 0 || static_cast<size_t>(index) >= index_to_node.size()) {
                throw std::out_of_range("get_neighbors_indices: Index out of range");
            }
            return adjac[index];
        }

        std::vector<Node> get_nodes() const override {
            return index_to_node;
        }

        bool has_node(const Node& node) const override {
            return node_to_index.find(node) != node_to_index.end();
        }

        void print() const override {
            std::cout  << "Graph (order: " << get_order() << ", size: " << get_size() << "):\n";
            for(size_t i = 0; i < index_to_node.size(); ++i) {
                std::cout << index_to_node[i] << ": ";
                for(int neighbor_index : adjac[i]) {
                    std::cout << index_to_node[neighbor_index] << " ";
                }
                std::cout << "\n";
            }
            std::cout << std::endl;
        }

        int get_index(const Node& node) const override {
            auto it = node_to_index.find(node);
            if (it != node_to_index.end()) {
                return it->second;
            }
            return -1; 
        }

        Node get_node(int index) const override {
            if (index >= 0 && static_cast<size_t>(index) < index_to_node.size()) {
                return index_to_node[index];
            }
            throw std::out_of_range("get_node: Index out of range");
        }
    
        bool is_adjacent(const Node& u, const Node& v) const override {
            const auto& neighbors = adjac[get_index(u)];
            return std::find(neighbors.begin(), neighbors.end(), get_index(v)) != neighbors.end();
        }
};

#endif // DIRECTEDADJACENCYLISTGRAPH_H