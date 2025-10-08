#include "graph/IGraph.h"
#include "graph/UndirectedAdjacencyListGraph.h"
#include "graph/UndirectedAdjacencyMatrixGraph.h"
#include "graph/UndirectedIncidenceMatrixGraph.h"
#include "GraphAlgorithms.h"
#include "GraphIO.h"
#include "DivideBlocks.h"
#include "CheckBipartite.h"

#include <iostream>
#include <exception>
#include <string>

template <typename Derived, typename Base>
bool instance_of(Base* ptr) {
    return dynamic_cast<Derived*>(ptr) != nullptr;
}

void choose_file_and_populate_graph(IGraph<char>& graph) {
    std::cout << "Selecione um dos arquivos abaixo para construir o grafo:\n";

    for (int i = 0; i <= 3; i++) {
        std::cout << "  " << i + 1 << " - " << "data/GRAFO_" << i << ".txt\n";
    }

    std::cout << "\n";

    int op;

    std::cin >> op;

    std::cout << "\n";

    if (op < 0 || op > 3) {
        throw new std::invalid_argument("Invalid operation!");
    }

    populate_graph_from_file("data/GRAFO_" + std::to_string(op - 1) + ".txt", graph);
}

struct Option {
    int id;
    std::string label;
};

int main() {

    IGraph<char>* graph_ptr = NULL;
    bool is_directed;
    int type;

    while (true) {
        std::map<int, std::string> options;

        options.insert({1, "Criar grafo com lista de adjacência"});
        options.insert({2, "Criar grafo com matriz de adjacência"});
        options.insert({3, "Criar grafo com matriz de incidência"});

        if (graph_ptr != NULL && !is_directed) {
            if (type == 1) {
                options.insert({4, "Converter grafgo para matriz de adjacência"});
            } else if (type == 2) {
                options.insert({4, "Converter grafgo para lista de adjacência"});
            }
            options.insert({5, "Calcular o grau de cada vértce"});
            options.insert({6, "Determinar se dois vértices são adjacentes"});
            options.insert({7, "Determinar o número total de vértices"});
            options.insert({8, "Determinar o número total de arestas"});
            options.insert({9, "Incluir novo vértice"});
            options.insert({10, "Excluir um vértice existente"});
            options.insert({11, "Determinar se o grafo é conexo"});
            options.insert({12, "Determinar se o grafo é bipartido"});
            options.insert({13, "Busca em largura a partir de um vértice"});
            options.insert({14, "Busca em profundidade, com determinação de arestas de retorno, a partir de um vértice"});
            options.insert({15, "Determinar articulações e blocos"});
        }

        std::cout << "Selecione uma opção:\n";

        for (auto& option : options) {
            std::cout << "  " << option.first << " - " << option.second << "\n";
        }

        std::cout << "\n";

        int opt;

        std::cin >> opt;

        std::cout << "\n";

        if (options[opt] == "") {
            std::cout << "Invalid option!\n\n";

            continue;
        }

        if (opt == 1) {
            if (graph_ptr != NULL) {
                delete graph_ptr;
            }

            graph_ptr = new UndirectedAdjacencyListGraph<char>();
            type = 1;
            is_directed = false;
            choose_file_and_populate_graph(*graph_ptr);
            graph_ptr->print();
        } else if (opt == 2) {
            if (graph_ptr != NULL) {
                delete graph_ptr;
            }

            graph_ptr = new UndirectedAdjacencyMatrixGraph<char>();
            type = 2;
            is_directed = false;

            choose_file_and_populate_graph(*graph_ptr);
            graph_ptr->print();
        } else if (opt == 4) {
            IGraph<char>* new_graph;

            if (type == 1) {
                new_graph = new UndirectedAdjacencyMatrixGraph<char>();
                type = 2;
            } else {
                new_graph = new UndirectedAdjacencyListGraph<char>();
                type = 1;
            }

            copy_graph(*graph_ptr, *new_graph);
            delete graph_ptr;
            graph_ptr = new_graph;
            graph_ptr->print();
        } else if (opt == 12) {
            if (is_graph_bipartite(*graph_ptr)) {
                std::cout << "Grafo é bipartido\n\n";
            } else {
                std::cout << "Grafo não é bipartido\n\n";
            }
        } else if (opt == 15) {
            auto result = divide_blocks(*graph_ptr);

            std::cout << "Articulações:\n";

            for (char node : result.articulations) {
                std::cout << node << "\n";
            }

            std::cout << "\nBlocos:\n";
            for (const auto& block : result.blocks) {
                for (char node : block) {
                    std::cout << node << " ";
                }

                std::cout << "\n";
            }

            std::cout << "\n";
        }
    }
}
