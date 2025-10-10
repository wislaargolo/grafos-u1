
#include "../GraphAlgorithms.h"
#include "../GraphIO.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "Creating graph from file 'GRAFO_0.txt' with Undirected Adjacency List...\n";
    UndirectedAdjacencyListGraph<char> UALgraph;
    populate_graph_from_file("data/GRAFO_0.txt", UALgraph);
    std::cout << "Total quantity of nodes: " << UALgraph.get_order() << std::endl;
    std::cout << std::endl;

    std::cout << "Creating graph from file 'GRAFO_1.txt' with Undirected Adjacency Matrix...\n";
    UndirectedAdjacencyMatrixGraph<char> UAMgraph;
    populate_graph_from_file("data/GRAFO_1.txt", UAMgraph);
    std::cout << "Total quantity of nodes: " << UAMgraph.get_order() << std::endl;
    std::cout << std::endl;

    std::cout << "Creating graph from file 'GRAFO_2.txt' with Undirected Incidence Matrix...\n";
    UndirectedIncidenceMatrixGraph<int> UIMgraph;
    populate_graph_from_file("data/GRAFO_2.txt", UIMgraph);
    std::cout << "Total quantity of nodes: " << UIMgraph.get_order() << std::endl;
    std::cout << std::endl;

    std::cout << "Creating graph from file 'GRAFO_3.txt' with Undirected Adjacency List...\n";
    UndirectedAdjacencyListGraph<char> UALgraph2;
    populate_graph_from_file("data/GRAFO_3.txt", UALgraph2);
    std::cout << "Total quantity of nodes: " << UALgraph2.get_order() << std::endl;
    std::cout << std::endl;

    std::cout << "Creating graph from file 'DIGRAFO_0.txt' with Directed Adjacency List...\n";
    DirectedAdjacencyListGraph<char> DALgraph;
    populate_graph_from_file("data/DIGRAFO_0.txt", DALgraph);
    std::cout << "Total quantity of nodes: " << DALgraph.get_order() << std::endl;
    std::cout << std::endl;

    std::cout << "Creating graph from file 'DIGRAFO_1.txt' with Directed Adjacency List...\n";
    DirectedAdjacencyListGraph<int> DALgraph2;
    populate_graph_from_file("data/DIGRAFO_1.txt", DALgraph2);
    std::cout << "Total quantity of nodes: " << DALgraph2.get_order() << std::endl;
    std::cout << std::endl;

    std::cout << "Creating graph from file 'DIGRAFO_2.txt' with Directed Adjacency Matrix...\n";
    DirectedAdjacencyMatrixGraph<int> DAMgraph;
    populate_graph_from_file("data/DIGRAFO_2.txt", DAMgraph);
    std::cout << "Total quantity of nodes: " << DAMgraph.get_order() << std::endl;
    std::cout << std::endl;

    std::cout << "Creating graph from file 'DIGRAFO_3.txt' with Directed Incidence Matrix...\n";
    DirectedIncidenceMatrixGraph<char> DIMgraph;
    populate_graph_from_file("data/DIGRAFO_3.txt", DIMgraph);
    std::cout << "Total quantity of nodes: " << DIMgraph.get_order() << std::endl;
    std::cout << std::endl;

    return 0;
}
