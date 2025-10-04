#ifndef DFS_H
#define DFS_H

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <stack>
#include <optional>
#include <iostream>

#include "graph/IGraph.h"

enum class EdgeType {
    TREE,
    BACK,
    FORWARD,
    CROSS
};

template<typename Node>
struct Edge {
    Node from;
    Node to;
};

template<typename Node>
struct DFSResult {
    std::unordered_map<Node, int> discovery, exit;
    std::unordered_map<EdgeType, std::vector<Edge<Node>>> edges;
    std::unordered_map<Node, Node> parent;
};


template<typename Node, class FindTree, class FindBack, class FindForward, class FindCross>
void dfs_visit(const IGraph<Node>& graph, const Node& node, int& time,
           std::unordered_map<Node, int>& discovery,
           std::unordered_map<Node, int>& exit,
           std::unordered_map<Node, Node>& parent,
           std::unordered_map<EdgeType, std::vector<Edge<Node>>>& edges,
           FindTree find_tree, FindBack find_back, 
           FindForward find_forward, FindCross find_cross) {
    discovery[node] = ++time;

    for (const auto& neighbor : graph.get_neighbors(node)) {
        if (discovery.find(neighbor) == discovery.end()) {
            parent[neighbor] = node;
            find_tree(node, neighbor);
            dfs_visit(graph, neighbor, time, discovery, exit, parent, edges, find_tree, find_back, find_forward, find_cross);
        } else if (exit.find(neighbor) == exit.end()){
            find_back(node, neighbor);
        } else if (discovery[node] < discovery[neighbor]) {
            find_forward(node, neighbor);
        } else {
            find_cross(node, neighbor);
        }
    }

    exit[node] = ++time;
}


template<typename Node>
DFSResult<Node> dfs(const IGraph<Node>& graph) {
    DFSResult<Node> result;
    int time = 0;

    auto find_tree = [&result](const Node& from, const Node& to) {
        result.edges[EdgeType::TREE].push_back({from, to});
    };

    auto find_back = [&result](const Node& from, const Node& to) {
        result.edges[EdgeType::BACK].push_back({from, to});
    };

    auto find_forward = [&result](const Node& from, const Node& to) {
        result.edges[EdgeType::FORWARD].push_back({from, to});
    };

    auto find_cross = [&result](const Node& from, const Node& to) {
        result.edges[EdgeType::CROSS].push_back({from, to});
    };

    while(graph.get_nodes().size() > result.discovery.size()) {
        Node start;
        for (const auto& node : graph.get_nodes()) {
            if (result.discovery.find(node) == result.discovery.end()) {
                start = node;
                break;
            }
        }

        dfs_visit(graph, start, time, result.discovery, result.exit, result.parent, result.edges,
              find_tree, find_back, find_forward, find_cross);
        
    }
    return result;
}

template<typename Node>
DFSResult<Node> dfs_unidirectional(const IGraph<Node>& graph, const Node& start) {
    if (!graph.has_node(start)) {
        throw std::invalid_argument("Start node does not exist in the graph.");
    }

    DFSResult<Node> result;
    int time = 0;

    auto find_tree = [&](const Node& from, const Node& to) {
        result.edges[EdgeType::TREE].push_back({from, to});
    };

    auto find_back = [&](const Node& from, const Node& to) {
        if(result.parent.count(from) && result.parent[from] != to) {
            result.edges[EdgeType::BACK].push_back({from, to});
        }
    };

    auto empty = [](const Node& from, const Node& to) {};

    dfs_visit(graph, start, time, result.discovery, result.exit, result.parent, result.edges,
          find_tree, find_back, empty, empty);

    return result;
}

template<typename Node>
std::vector<Node> dfs_pre_order(const DFSResult<Node>& dfs_result) {
    
    std::vector<Node> pre_order;
    pre_order.reserve(dfs_result.discovery.size());
    for (const auto& [node, time] : dfs_result.discovery) {
        pre_order.push_back(node);
    }

    std::sort(pre_order.begin(), pre_order.end(),
              [&](const Node& a, const Node& b) {
                  return dfs_result.discovery.at(a) < dfs_result.discovery.at(b);
              });

    return pre_order;

}

#endif // DFS_H