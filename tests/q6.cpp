#include "../GraphAlgorithms.h"
#include "../GraphIO.h"

#include <iostream>
#include <string>


void test_is_adjacent(char u, char v, const IGraph<char>& graph) {
    std::cout << "Testing is_adjacent method:\n";
    std::cout << "Is '" << u << "' adjacent to '" << v << "'? "
              << (graph.is_adjacent(u, v) ? "Yes" : "No") << "\n";
}

int main() {
    //cria digrafo usando lista de adjacencia e printa o digrafo
    std::cout << "Creating graph from file 'DIGRAFO_0.txt' to adjacency list...\n";
    DirectedAdjacencyListGraph<char> DALgraph;
    populate_graph_from_file("data/DIGRAFO_0.txt", DALgraph);
    DALgraph.print();

    //testa o metodo is_adjacent
    test_is_adjacent('a', 'b', DALgraph);
    test_is_adjacent('a', 'c', DALgraph);
    test_is_adjacent('b', 'd', DALgraph);

    //cria grafo usando lista de adjacencia e printa o grafo
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency list...\n";
    UndirectedAdjacencyListGraph<char> UALgraph;
    populate_graph_from_file("data/GRAFO_0.txt", UALgraph);
    UALgraph.print();

    //testa o metodo is_adjacent
    test_is_adjacent('a', 'b', UALgraph);
    test_is_adjacent('a', 'c', UALgraph);
    test_is_adjacent('b', 'd', UALgraph);

    //cria digrafo usando matriz de adjacencia e printa o digrafo
    std::cout << "Creating graph from file 'DIGRAFO_0.txt' to adjacency matrix...\n";
    DirectedAdjacencyMatrixGraph<char> DAMgraph;
    populate_graph_from_file("data/DIGRAFO_0.txt", DAMgraph);
    DAMgraph.print();

    //testa o metodo is_adjacent
    test_is_adjacent('a', 'b', DAMgraph);
    test_is_adjacent('a', 'c', DAMgraph);
    test_is_adjacent('b', 'd', UALgraph);

    //cria grafo usando matriz de adjacencia e printa o grafo
    std::cout << "Creating graph from file 'GRAFO_0.txt' to adjacency matrix...\n";
    UndirectedAdjacencyMatrixGraph<char> UAMgraph;
    populate_graph_from_file("data/GRAFO_0.txt", UAMgraph);
    UAMgraph.print();

    //testa o metodo is_adjacent
    test_is_adjacent('a', 'b', UAMgraph);
    test_is_adjacent('a', 'c', UAMgraph);
    test_is_adjacent('b', 'd', UAMgraph);

    //cria digrafo usando matriz de incidencia e printa o grafo
    std::cout << "Creating graph from file 'DIGRAFO_0.txt' to incidence matrix...\n";
    DirectedIncidenceMatrixGraph<char> DIMgraph;
    populate_graph_from_file("data/DIGRAFO_0.txt", DIMgraph);
    DIMgraph.print();

    //testa o metodo is_adjacent
    test_is_adjacent('a', 'b', DIMgraph);
    test_is_adjacent('a', 'c', DIMgraph);
    test_is_adjacent('b', 'd', DIMgraph);

    return 0;
}
