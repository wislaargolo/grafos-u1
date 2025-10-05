#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "IGraph.h"
#include "DirectedAdjacencyListGraph.h"
#include "DirectedAdjacencyMatrixGraph.h"
#include "UndirectedAdjacencyListGraph.h"
#include "UndirectedAdjacencyMatrixGraph.h"

using std::string;
using std::vector;

// Helpers para assertions sem gmock
template <class T>
static void ExpectVecEq(const std::vector<T>& a, const std::vector<T>& b) {
    EXPECT_EQ(a, b);
}
template <class T>
static void ExpectUnorderedEq(std::vector<T> a, std::vector<T> b) {
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    EXPECT_EQ(a, b);
}
template <class T>
static void ExpectEmpty(const std::vector<T>& v) { EXPECT_TRUE(v.empty()); }

// Captura de cout para testar print()
struct CoutCapture {
    std::streambuf* oldBuf{nullptr};
    std::ostringstream oss;
    void begin() { oldBuf = std::cout.rdbuf(oss.rdbuf()); }
    std::string end() { std::cout.rdbuf(oldBuf); return oss.str(); }
};

// -------------------------
// DirectedAdjacencyListGraph
// -------------------------

TEST(DirectedAdjacencyListGraph, InitiallyEmpty) {
    DirectedAdjacencyListGraph<int> g;
    EXPECT_EQ(g.get_order(), 0u);
    EXPECT_EQ(g.get_size(), 0u);
    EXPECT_FALSE(g.has_node(1));
    ExpectEmpty(g.get_nodes());
}

TEST(DirectedAdjacencyListGraph, AddNodeIdempotentAndIndexing) {
    DirectedAdjacencyListGraph<string> g;
    g.add_node("A");
    g.add_node("A"); // idempotente
    g.add_node("B");

    EXPECT_EQ(g.get_order(), 2u);
    EXPECT_TRUE(g.has_node("A"));
    EXPECT_TRUE(g.has_node("B"));
    EXPECT_NE(g.get_index("A"), -1);
    EXPECT_NE(g.get_index("B"), -1);

    int ia = g.get_index("A");
    int ib = g.get_index("B");
    EXPECT_EQ(g.get_node(ia), "A");
    EXPECT_EQ(g.get_node(ib), "B");
}

TEST(DirectedAdjacencyListGraph, AddEdgeCreatesNodesAndNoDuplicates) {
    DirectedAdjacencyListGraph<int> g;
    g.add_edge(1, 2);
    g.add_edge(1, 2); // duplicada não conta

    EXPECT_EQ(g.get_order(), 2u);
    EXPECT_EQ(g.get_size(), 1u);
    ExpectVecEq(g.get_neighbors(1), std::vector<int>{2});
    ExpectEmpty(g.get_neighbors(2));

    auto idxs = g.get_neighbors_indices(g.get_index(1));
    ASSERT_EQ(idxs.size(), 1u);
    int i2 = g.get_index(2);
    EXPECT_EQ(idxs[0], i2);
}

TEST(DirectedAdjacencyListGraph, RemoveEdgeIsIdempotent) {
    DirectedAdjacencyListGraph<int> g;
    g.add_edge(1, 2);
    g.remove_edge(1, 2);
    g.remove_edge(1, 2);
    EXPECT_EQ(g.get_size(), 0u);
    ExpectEmpty(g.get_neighbors(1));
}

TEST(DirectedAdjacencyListGraph, RemoveNodeUpdatesMappingsAndEdges) {
    DirectedAdjacencyListGraph<int> g;
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(1, 3);

    g.remove_node(2);
    EXPECT_FALSE(g.has_node(2));
    EXPECT_EQ(g.get_order(), 2u);

    EXPECT_EQ(g.get_size(), 1u);
    ExpectVecEq(g.get_neighbors(1), std::vector<int>{3});

    int i1 = g.get_index(1);
    int i3 = g.get_index(3);
    EXPECT_NE(i1, -1);
    EXPECT_NE(i3, -1);
    EXPECT_EQ(g.get_node(i1), 1);
    EXPECT_EQ(g.get_node(i3), 3);
}

TEST(DirectedAdjacencyListGraph, GetNodeInvalidIndexThrows) {
    DirectedAdjacencyListGraph<int> g;
    g.add_node(10);
    EXPECT_THROW(g.get_node(-1), std::out_of_range);
    EXPECT_THROW(g.get_node(1), std::out_of_range);
}

TEST(DirectedAdjacencyListGraph, GetNeighborsIndicesInvalidIndexThrows) {
    DirectedAdjacencyListGraph<int> g;
    g.add_node(10);
    EXPECT_NO_THROW(g.get_neighbors_indices(0));
    EXPECT_THROW(g.get_neighbors_indices(-1), std::out_of_range);
    EXPECT_THROW(g.get_neighbors_indices(1), std::out_of_range);
}

TEST(DirectedAdjacencyListGraph, PrintContainsKeyInfo) {
    DirectedAdjacencyListGraph<string> g;
    g.add_edge("A", "B");
    CoutCapture cap; cap.begin();
    g.print();
    auto out = cap.end();
    EXPECT_NE(out.find("order: 2"), std::string::npos);
    EXPECT_NE(out.find("size: 1"), std::string::npos);
    EXPECT_NE(out.find("A:"), std::string::npos);
    EXPECT_NE(out.find("B"), std::string::npos);
}

// -------------------------
// DirectedAdjacencyMatrixGraph
// -------------------------

TEST(DirectedAdjacencyMatrixGraph, InitiallyEmpty) {
    DirectedAdjacencyMatrixGraph<int> g;
    EXPECT_EQ(g.get_order(), 0u);
    EXPECT_EQ(g.get_size(), 0u);
    EXPECT_FALSE(g.has_node(1));
    ExpectEmpty(g.get_nodes());
}

TEST(DirectedAdjacencyMatrixGraph, ConstructorWithInitialNodes) {
    DirectedAdjacencyMatrixGraph<string> g({"A","B","C"});
    EXPECT_EQ(g.get_order(), 3u);
    EXPECT_TRUE(g.has_node("A"));
    EXPECT_TRUE(g.has_node("B"));
    EXPECT_TRUE(g.has_node("C"));
}

TEST(DirectedAdjacencyMatrixGraph, AddNodeIdempotent) {
    DirectedAdjacencyMatrixGraph<int> g;
    g.add_node(1);
    g.add_node(1);
    EXPECT_EQ(g.get_order(), 1u);
}

TEST(DirectedAdjacencyMatrixGraph, AddEdgeCreatesNodes) {
    DirectedAdjacencyMatrixGraph<int> g;
    g.add_edge(1, 2);
    EXPECT_EQ(g.get_order(), 2u);
    EXPECT_EQ(g.get_size(), 1u);
    ExpectVecEq(g.get_neighbors(1), std::vector<int>{2});
    ExpectEmpty(g.get_neighbors(2));
}

TEST(DirectedAdjacencyMatrixGraph, RemoveEdgeIsIdempotent) {
    DirectedAdjacencyMatrixGraph<int> g;
    g.add_edge(1, 2);
    g.remove_edge(1, 2);
    g.remove_edge(1, 2);
    EXPECT_EQ(g.get_size(), 0u);
}

TEST(DirectedAdjacencyMatrixGraph, RemoveNodeThrowsIfMissing) {
    DirectedAdjacencyMatrixGraph<int> g;
    g.add_node(10);
    EXPECT_THROW(g.remove_node(11), std::runtime_error);
}

TEST(DirectedAdjacencyMatrixGraph, RemoveNodeCompactsMatrixAndMappings) {
    DirectedAdjacencyMatrixGraph<int> g;
    g.add_edge(1,2);
    g.add_edge(2,3);
    g.add_edge(1,3);

    g.remove_node(2);
    EXPECT_FALSE(g.has_node(2));
    EXPECT_EQ(g.get_order(), 2u);

    EXPECT_EQ(g.get_size(), 1u);
    ExpectVecEq(g.get_neighbors(1), std::vector<int>{3});
}

TEST(DirectedAdjacencyMatrixGraph, IndexingAndAccessors) {
    DirectedAdjacencyMatrixGraph<string> g;
    g.add_node("X");
    g.add_node("Y");
    int ix = g.get_index("X");
    int iy = g.get_index("Y");
    EXPECT_NE(ix, -1);
    EXPECT_NE(iy, -1);
    EXPECT_EQ(g.get_node(ix), "X");
    EXPECT_EQ(g.get_node(iy), "Y");
    EXPECT_THROW(g.get_node(-1), std::out_of_range);
    EXPECT_THROW(g.get_node(2), std::out_of_range);
}

TEST(DirectedAdjacencyMatrixGraph, GetNeighborsIndices) {
    DirectedAdjacencyMatrixGraph<int> g;
    g.add_edge(1,2);
    g.add_edge(1,3);
    int i1 = g.get_index(1);
    int i2 = g.get_index(2);
    int i3 = g.get_index(3);
    auto idxs = g.get_neighbors_indices(i1);
    ExpectUnorderedEq<int>(idxs, std::vector<int>{i2, i3});
    EXPECT_THROW(g.get_neighbors_indices(-1), std::out_of_range);
    EXPECT_THROW(g.get_neighbors_indices(42), std::out_of_range);
}

TEST(DirectedAdjacencyMatrixGraph, PrintContainsMatrixAndCounts) {
    DirectedAdjacencyMatrixGraph<string> g({"A","B"});
    g.add_edge("A","B");
    CoutCapture cap; cap.begin();
    g.print();
    auto out = cap.end();
    EXPECT_NE(out.find("directed"), std::string::npos);
    EXPECT_NE(out.find("order: 2"), std::string::npos);
    EXPECT_NE(out.find("size: 1"), std::string::npos);
    EXPECT_NE(out.find("Adjacency Matrix"), std::string::npos);
    EXPECT_NE(out.find("A"), std::string::npos);
    EXPECT_NE(out.find("B"), std::string::npos);
}

// -------------------------
// UndirectedAdjacencyListGraph
// -------------------------

TEST(UndirectedAdjacencyListGraph, AddEdgeAddsBothDirectionsAndSizeCounts) {
    UndirectedAdjacencyListGraph<int> g;
    g.add_edge(1,2);
    EXPECT_EQ(g.get_size(), 1u);
    ExpectVecEq(g.get_neighbors(1), std::vector<int>{2});
    ExpectVecEq(g.get_neighbors(2), std::vector<int>{1});

    g.add_edge(2,1);
    EXPECT_EQ(g.get_size(), 1u);
}

TEST(UndirectedAdjacencyListGraph, LoopsCountOnce) {
    UndirectedAdjacencyListGraph<int> g;
    g.add_edge(1,1);
    EXPECT_EQ(g.get_size(), 1u);
    ExpectVecEq(g.get_neighbors(1), std::vector<int>{1});
}

TEST(UndirectedAdjacencyListGraph, RemoveEdgeRemovesBothWays) {
    UndirectedAdjacencyListGraph<int> g;
    g.add_edge(1,2);
    g.remove_edge(1,2);
    EXPECT_EQ(g.get_size(), 0u);
    ExpectEmpty(g.get_neighbors(1));
    ExpectEmpty(g.get_neighbors(2));
}

// -------------------------
// UndirectedAdjacencyMatrixGraph
// -------------------------

TEST(UndirectedAdjacencyMatrixGraph, SizeIsHalfDirectedCount) {
    UndirectedAdjacencyMatrixGraph<int> g;
    g.add_edge(1,2);
    EXPECT_EQ(g.get_size(), 1u);
}

TEST(UndirectedAdjacencyMatrixGraph, AddEdgeAddsSymmetrically) {
    UndirectedAdjacencyMatrixGraph<string> g;
    g.add_edge("A","B");
    ExpectVecEq(g.get_neighbors("A"), std::vector<string>{"B"});
    ExpectVecEq(g.get_neighbors("B"), std::vector<string>{"A"});
}

TEST(UndirectedAdjacencyMatrixGraph, RemoveEdgeRemovesSymmetrically) {
    UndirectedAdjacencyMatrixGraph<int> g;
    g.add_edge(1,2);
    g.remove_edge(1,2);
    ExpectEmpty(g.get_neighbors(1));
    ExpectEmpty(g.get_neighbors(2));
    EXPECT_EQ(g.get_size(), 0u);
}

TEST(UndirectedAdjacencyMatrixGraph, PrintContainsMatrixAndCounts) {
    UndirectedAdjacencyMatrixGraph<string> g;
    g.add_edge("A","B");
    CoutCapture cap; cap.begin();
    g.print();
    auto out = cap.end();
    EXPECT_NE(out.find("undirected"), std::string::npos);
    EXPECT_NE(out.find("order: 2"), std::string::npos);
    EXPECT_NE(out.find("size: 1"), std::string::npos);
    EXPECT_NE(out.find("Adjacency Matrix"), std::string::npos);
}

// -------------------------
// Casos mistos e robustez
// -------------------------

TEST(MixedGraphs, RemoveNonExistingNodeNoThrowOnListButThrowOnMatrix) {
    DirectedAdjacencyListGraph<int> gl;
    gl.add_node(1);
    EXPECT_NO_THROW(gl.remove_node(2));

    DirectedAdjacencyMatrixGraph<int> gm;
    gm.add_node(1);
    EXPECT_THROW(gm.remove_node(2), std::runtime_error);
}

TEST(MixedGraphs, GetNeighborsOnMissingNodeReturnsEmpty) {
    DirectedAdjacencyListGraph<int> gl;
    DirectedAdjacencyMatrixGraph<int> gm;
    ExpectEmpty(gl.get_neighbors(999));
    ExpectEmpty(gm.get_neighbors(999));
}

TEST(MixedGraphs, AddEdgeSelfLoopBehaviors) {
    DirectedAdjacencyListGraph<int> gl;
    gl.add_edge(7,7);
    EXPECT_EQ(gl.get_size(), 1u);
    ExpectVecEq(gl.get_neighbors(7), std::vector<int>{7});

    DirectedAdjacencyMatrixGraph<int> gm;
    gm.add_edge(5,5);
    EXPECT_EQ(gm.get_size(), 1u);
    ExpectVecEq(gm.get_neighbors(5), std::vector<int>{5});
}

