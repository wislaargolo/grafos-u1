#ifndef DFS_H
#define DFS_H

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <stack>
#include <optional>
#include <iostream>
#include <numeric> 

#include "graph/IGraph.h"

enum class EdgeType {
    TREE,
    BACK,
    FORWARD,
    CROSS
};

template<typename Node>
struct Edge {
    Node from, to;
};

template<typename Node>
struct DFSState {
    std::vector<int> discovery, exit;
    std::vector<int> parent;
    std::unordered_map<EdgeType, std::vector<Edge<Node>>> edges;

    DFSState(size_t num_nodes = 0)
        : discovery(num_nodes, 0),                            
          exit(num_nodes, 0),                              
          parent(num_nodes, -1)            
    {}
};

template<typename Node>
struct DFSResult {
    std::unordered_map<Node, int> discovery, exit;
    std::unordered_map<EdgeType, std::vector<Edge<Node>>> edges;
};



template<typename Node, class FindTree, class FindBack, class FindForward, class FindCross>
void dfs_visit(const IGraph<Node>& graph, 
            int node, int& time,
            std::vector<int>& discovery, std::vector<int>& exit,
            std::vector<int>& parent,
            FindTree find_tree, FindBack find_back, 
            FindForward find_forward, FindCross find_cross) {
    discovery[node] = ++time;

    for(int neighbor_index : graph.get_neighbors_indices(node)) {
        if (discovery[neighbor_index] == 0) { 
            parent[neighbor_index] = node;
            find_tree(node, neighbor_index);
            dfs_visit(graph, neighbor_index, time, discovery, exit, parent,
                      find_tree, find_back, find_forward, find_cross);
        } else if (exit[neighbor_index] == 0) { 
            find_back(node, neighbor_index);
        } else if (discovery[node] < discovery[neighbor_index]) { 
            find_forward(node, neighbor_index);
        } else { 
            find_cross(node, neighbor_index);
        }
    }

    exit[node] = ++time;
}


template<typename Node>
DFSResult<Node> dfs(const IGraph<Node>& graph) {
    DFSState<Node> state(graph.get_order());
    int time = 0;

    auto find_tree =[&](int from, int to) {
        state.edges[EdgeType::TREE].push_back({graph.get_node(from), graph.get_node(to)});
    };
    auto find_back = [&](int from, int to) {
        state.edges[EdgeType::BACK].push_back({graph.get_node(from), graph.get_node(to)});
    };
    auto find_forward = [&](int from, int to) {
        state.edges[EdgeType::FORWARD].push_back({graph.get_node(from), graph.get_node(to)});
    };
    auto find_cross = [&](int from, int to) {
        state.edges[EdgeType::CROSS].push_back({graph.get_node(from), graph.get_node(to)});
    };

    
    for(int i = 0; i < graph.get_order(); i++) {
        if (state.discovery[i] == 0) {
            dfs_visit(graph, i, time, state.discovery, state.exit, state.parent,
                      find_tree, find_back, find_forward, find_cross);
        }
    }

    return get_result_dfs(graph, state);
}

template<typename Node>
DFSResult<Node> dfs_unidirectional(const IGraph<Node>& graph, const Node& start) {
    if (!graph.has_node(start)) {
        throw std::invalid_argument("Start node does not exist in the graph.");
    }

    DFSState<Node> state(graph.get_order());
    int time = 0;

    auto find_tree = [&](int from, int to) {
        state.edges[EdgeType::TREE].push_back({graph.get_node(from), graph.get_node(to)});
    };

    auto find_back = [&](int from, int to) {
        if(state.parent[from] != -1 && state.parent[from] != to) {
            state.edges[EdgeType::BACK].push_back({graph.get_node(from), graph.get_node(to)});
        }
    };

    auto empty = [](int from, int to) {};

    dfs_visit(graph, graph.get_index(start), time, state.discovery, state.exit, state.parent,
          find_tree, find_back, empty, empty);

    return get_result_dfs(graph, state);
}

template<typename Node>
DFSResult<Node> get_result_dfs(const IGraph<Node>& graph, const DFSState<Node>& state) {
    DFSResult<Node> result;

    for(size_t i = 0; i < graph.get_order(); i++) {
        Node node = graph.get_node(i);
        result.discovery[node] = state.discovery[i];
        result.exit[node] = state.exit[i];
    }
    result.edges = state.edges;

    return result;
}
#endif // DFS_H