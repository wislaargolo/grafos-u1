#ifndef UNDIRECTEDADJACENCYLISTGRAPH_H
#define UNDIRECTEDADJACENCYLISTGRAPH_H
#include <algorithm> 

//talvez mudar pra composição ao invés de herança
#include "DirectedAdjacencyListGraph.h" 

template<typename Node>
class UndirectedAdjacencyListGraph : public DirectedAdjacencyListGraph<Node> {
    
    public:
        void add_edge(const Node& u, const Node& v) override {
            DirectedAdjacencyListGraph<Node>::add_edge(u, v);
            if (u != v) {
                DirectedAdjacencyListGraph<Node>::add_edge(v, u);
            }
        }

        void remove_edge(const Node& u, const Node& v) override {
            DirectedAdjacencyListGraph<Node>::remove_edge(u, v);
            if (u != v) {
                DirectedAdjacencyListGraph<Node>::remove_edge(v, u);
            }
        }

        size_t get_size() const override {
           size_t directed_size = DirectedAdjacencyListGraph<Node>::get_size();
           size_t loop_count = 0;

           for(const auto& node : DirectedAdjacencyListGraph<Node>::get_nodes()) {
               const auto& neighbors = DirectedAdjacencyListGraph<Node>::get_neighbors(node);
               loop_count += std::count(neighbors.begin(), neighbors.end(), node);
           }

           size_t regular_edges = (directed_size - loop_count) / 2;
           return regular_edges + loop_count;
        }
};
#endif // UNDIRECTEDADJACENCYLISTGRAPH_H