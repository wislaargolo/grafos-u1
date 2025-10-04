#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include "graph/UndirectedAdjacencyListGraph.h"

template<typename Node>
std::vector<Node> bfs(const IGraph<Node>& graph, Node start) {

    if (!graph.has_node(start)) {
        std::cerr << "Start node '" << start << "' does not exist in the graph.\n";
        return {};
    }

    int start_index = graph.get_index(start);
    size_t order = graph.get_order();

    std::vector<size_t> visited(order, 0);
    std::queue<size_t> queue;
    std::vector<Node> result;

    visited[start_index] = 1;
    queue.push(start_index);

    while (!queue.empty()) {
        size_t current = queue.front();
        queue.pop();
        result.push_back(graph.get_node(current));

        for(size_t neighbor_index : graph.get_neighbors_indices(current)) {
            if (visited[neighbor_index] == 0) {
                visited[neighbor_index] = 1;
                queue.push(neighbor_index);

            }
        }
     }
     return result;
    
}
