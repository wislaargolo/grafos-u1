#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include "graph/UndirectedAdjacencyListGraph.h"

template<typename Node>
std::vector<Node> bfs(const IGraph<Node>& graph, Node start) {
    std::vector<Node> visited;
    std::queue<Node> queue;

    if (!graph.has_node(start)) {
        std::cerr << "Start node '" << start << "' does not exist in the graph.\n";
        return visited; 
    }

    visited.push_back(start);
    queue.push(start);

    while (!queue.empty()) {
        Node current = queue.front();
        queue.pop();

        for (const auto& neighbor : graph.get_neighbors(current)) {
            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                visited.push_back(neighbor);
                queue.push(neighbor);
            }
        }
    }

    return visited;
}
