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
        std::unordered_map<Node, std::vector<Node>> adjList;
    public:

        size_t get_order() const override {
            return adjList.size();
        }

        size_t get_size() const override {
            size_t edge_count = 0;
            for (const auto& [key, neighbors] : adjList) {
                edge_count += neighbors.size();
            }
            return edge_count;
        }

        void add_node(const Node& node) override {
            adjList[node];
        }

        void remove_node(const Node& node) override {
            adjList.erase(node);
            for (auto& [key, neighbors] : adjList) {
                neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), node), neighbors.end());
            }
        }

        void add_edge(const Node& from, const Node& to) override {
            adjList[from].push_back(to);
        }

        void remove_edge(const Node& from, const Node& to) override {
            if (has_node(from)) {
                auto& neighbors_from = adjList.at(from);
                neighbors_from.erase(std::remove(neighbors_from.begin(), neighbors_from.end(), to), neighbors_from.end());
            }
        }

        std::vector<Node> get_neighbors(const Node& node) const override {
            if (has_node(node)) {
                return adjList.at(node);
            }
            return {};
        }

        std::vector<Node> get_nodes() const override {
            std::vector<Node> nodes;
            for (const auto& [key, neighbors] : adjList) {
                nodes.push_back(key);
            }
            return nodes;
        }

        bool has_node(const Node& node) const override {
            return adjList.count(node) > 0;
        }

        void print() const override {
            std::cout  << "Graph (order: " << get_order() << ", size: " << get_size() << "):\n";
            for (const auto& [key, neighbors] : adjList) {
                std::cout << key << ": ";
                for (const auto& neighbor : neighbors) {
                    std::cout << neighbor << " ";
                }
                std::cout << "\n";
            }
            std::cout << std::endl;
        }
};

#endif // DIRECTEDADJACENCYLISTGRAPH_H