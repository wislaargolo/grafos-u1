#ifndef DIVIDE_BLOCKS_H
#define DIVIDE_BLOCKS_H

#include <vector>
#include <set>
#include <iostream>
#include <stdexcept>
#include <list>

#include "./graph/IGraph.h"

struct DivideBlocksState {
    std::vector<std::list<int>> blocks;
    std::vector<int> articulations;
    std::vector<int> discovery;
    std::vector<int> depth;
    std::vector<int> lowpt;
};

template<typename Node>
struct DivideBlocksResult {
    std::vector<std::vector<Node>> blocks;
    std::vector<Node> articulations;
};

template<typename Node>
std::list<int> divide_blocks_visit(const IGraph<Node>& graph, DivideBlocksState& state, int node, int parent = -1) {
    state.discovery[node] = 1;

    bool is_root = parent == -1;
    bool is_articulation = false;
    int self_lowpt = node;
    int number_of_children = 0;
    std::list<int> block;

    for (int neighbor_index : graph.get_neighbors_indices(node)) {
        if (state.discovery[neighbor_index] == 0) {
            number_of_children++;

            state.depth[neighbor_index] = state.depth[node] + 1;
            std::list<int> child_block = divide_blocks_visit(graph, state, neighbor_index, node);

            int child_lowpt = state.lowpt[neighbor_index];

            if (state.depth[child_lowpt] < state.depth[self_lowpt]) {
                self_lowpt = child_lowpt;
            }

            if (is_root || child_lowpt == neighbor_index || child_lowpt == node) {
                is_articulation = !is_root || number_of_children > 1;

                child_block.push_front(node);

                state.blocks.push_back(std::move(child_block));
            } else {
                block.splice(block.end(), child_block);
            }
        } else if (parent != neighbor_index) {
            if (state.depth[neighbor_index] < state.depth[self_lowpt]) {
                self_lowpt = neighbor_index;
            }
        }
    }

    state.lowpt[node] = self_lowpt;

    if (is_articulation) {
        state.articulations.push_back(node);
    }

    block.push_front(node);

    return block;
}

template<typename Node>
DivideBlocksResult<Node> divide_blocks(const IGraph<Node>& graph) {
    if (graph.get_nodes().size() == 0) {
        throw std::invalid_argument("Graph is empty");
    }

    DivideBlocksState state;

    size_t size = graph.get_size();

    state.discovery.resize(size, 0);
    state.depth.resize(size);
    state.lowpt.resize(size);
    state.depth[0] = 0;

    divide_blocks_visit(graph, state, 0);

    DivideBlocksResult<Node> result;

    for (std::list<int>& index_block : state.blocks) {
        std::vector<Node> block;

        for (int index : index_block) {
            block.push_back(graph.get_node(index));
        }

        result.blocks.push_back(std::move(block));
    }

    for (int index : state.articulations) {
        result.articulations.push_back(graph.get_node(index));
    }

    return result;
}

#endif
