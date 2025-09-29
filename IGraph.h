#ifndef IGRAPH_H
#define IGRAPH_H

#include <vector>

template<typename Node>
class IGraph {
public:
    virtual ~IGraph() = default;

    virtual size_t get_order() const = 0;
    virtual size_t get_size() const = 0;

    virtual void add_node(const Node& node) = 0;
    virtual void remove_node(const Node& node) = 0;
    virtual void add_edge(const Node& from, const Node& to) = 0;
    virtual void remove_edge(const Node& from, const Node& to) = 0;

    virtual std::vector<Node> get_neighbors(const Node& node) const = 0;
    virtual std::vector<Node> get_nodes() const = 0;

    virtual bool has_node(const Node& node) const = 0;

    virtual void print() const = 0;

};

#endif // IGRAPH_H