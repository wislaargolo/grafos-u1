#include "graph/IGraph.h"
#include "graph/UndirectedAdjacencyListGraph.h"
#include "graph/UndirectedAdjacencyMatrixGraph.h"
#include "graph/UndirectedIncidenceMatrixGraph.h"
#include "GraphAlgorithms.h"
#include "GraphIO.h"
#include "DivideBlocks.h"
#include "CheckBipartite.h"
#include "Bfs.h"
#include "Dfs.h"

#include <iostream>
#include <exception>
#include <string>

template <typename Derived, typename Base>
bool instance_of(Base* ptr) {
    return dynamic_cast<Derived*>(ptr) != nullptr;
}

void choose_file_and_populate_graph(IGraph<char>& graph, bool is_directed = false) {
    std::cout << "Selecione um dos arquivos abaixo para construir o grafo:\n";

    for (int i = 0; i <= 3; i++) {
        std::cout << "  " << i + 1 << " - " << (is_directed ? "data/DIGRAFO_" : "data/GRAFO_") << i << ".txt\n";
    }

    std::cout << "\n";

    int op;

    std::cin >> op;

    std::cout << "\n";

    if (op < 0 || op > 3) {
        throw new std::invalid_argument("Invalid operation!");
    }

    populate_graph_from_file((is_directed ? "data/DIGRAFO_" : "data/GRAFO_") + std::to_string(op - 1) + ".txt", graph);
}

void print_nodes(IGraph<char>& graph) {
    std::cout << "Vértices: ";

    for (char node : graph.get_nodes()) {
        std::cout << node << " ";
    }

    std::cout << "\n";
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
                options.insert({4, "Converter grafo para matriz de adjacência"});
            } else if (type == 2) {
                options.insert({4, "Converter grafo para lista de adjacência"});
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

        options.insert({16, "Criar digrafo com matriz de adjacência"});
        options.insert({17, "Criar digrafo com matriz de incidência"});

        if (graph_ptr != NULL && is_directed) {
            options.insert({18, "Determinar grafo subjacente"});
            options.insert({19, "Busca em largura"});
            options.insert({20, "Busca em profundidade, com determinação de tipos de aresta"});
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
        }

        else if (opt == 2) {
            if (graph_ptr != NULL) {
                delete graph_ptr;
            }

            graph_ptr = new UndirectedAdjacencyMatrixGraph<char>();
            type = 2;
            is_directed = false;

            choose_file_and_populate_graph(*graph_ptr);
            graph_ptr->print();
        }

        else if (opt == 3) {
            if (graph_ptr != NULL) {
                delete graph_ptr;
            }

            graph_ptr = new UndirectedIncidenceMatrixGraph<char>();
            type = 3;
            is_directed = false;

            choose_file_and_populate_graph(*graph_ptr);
            graph_ptr->print();
        }

        else if (opt == 4) {
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
        }

        else if (opt == 5) {
            graph_ptr->print();

            std::cout << "Calculando graus dos vertices:\n";
            for (const auto& node : graph_ptr->get_nodes()) {
                std::cout << "  Vertice " << node << ": "
                        << "Grau de Entrada (in-degree): " << graph_ptr->get_in_degree(node)
                        << ", Grau de Saida (out-degree): " << graph_ptr->get_out_degree(node)
                        << std::endl;
            }
            std::cout << "\n";
        }

        else if (opt == 6) {
            print_nodes(*graph_ptr);

            char n1, n2;

            std::cout << "Digite o vértice 1: ";
            std::cin >> n1;
            std::cout << "Digite o vértice 2: ";
            std::cin >> n2;

            graph_ptr->print();

            if (graph_ptr->is_adjacent(n1, n2)) {
                std::cout << "\nOs vértices são adjacentes.\n\n";
            } else {
                std::cout << "\nOs vértices não são adjacentes.\n\n";
            }
        }

        else if (opt == 7) {
            graph_ptr->print();

            std::cout << "Ordem do grafo: " << graph_ptr->get_order() << "\n\n";
        }

        else if (opt == 8) {
            graph_ptr->print();

            std::cout << "Tamanho do grafo: " << graph_ptr->get_size() << "\n\n";
        }

        else if (opt == 9) {
            print_nodes(*graph_ptr);

            char node;

            std::cout << "Digite um novo vértice: ";
            std::cin >> node;
            std::cout << "\n";

            graph_ptr->add_node(node);
            graph_ptr->print();
        }

        else if (opt == 10) {
            print_nodes(*graph_ptr);

            char node;

            std::cout << "Digite o vértice para excluir: ";
            std::cin >> node;
            std::cout << "\n";

            graph_ptr->remove_node(node);
            graph_ptr->print();
        }

        else if (opt == 11) {
            graph_ptr->print();

            if (is_connected(*graph_ptr)) {
                std::cout << "O grafo é conexo.\n\n";
            } else {
                std::cout << "O grafo não é conexo.\n\n";
            }
        }

        else if (opt == 12) {
            graph_ptr->print();

            if (is_graph_bipartite(*graph_ptr)) {
                std::cout << "Grafo é bipartido\n\n";
            } else {
                std::cout << "Grafo não é bipartido\n\n";
            }
        }

        else if (opt == 13) {
            print_nodes(*graph_ptr);

            char node;

            std::cout << "Digite o vértice para a busca em largura: ";
            std::cin >> node;
            std::cout << "\n";

            graph_ptr->print();

            std::cout << "Ordem dos vértices visitados: \n";

            auto bfs_result = bfs(*graph_ptr, node);

            for (const auto& node : bfs_result) {
                std::cout << node << " ";
            }

            std::cout << "\n\n";
        }

        else if (opt == 14) {
            print_nodes(*graph_ptr);

            char node;

            std::cout << "Digite o vértice para a busca em profundidade: ";
            std::cin >> node;
            std::cout << "\n";

            graph_ptr->print();

            std::cout << "Resultado:\n";

            auto dfs_result = dfs_unidirectional(*graph_ptr, node);

            for (const auto& [node, time] : dfs_result.discovery) {
                std::cout << "Vértice: " << node << ", Profundidade de Entrada: " << time
                        << ", Profundidade de Saída: " << dfs_result.exit.at(node) << "\n";
            }

            std::cout << "Arestas:\n";
            for (const auto& [type, edges] : dfs_result.edges) {
                std::cout << "Arestas de ";

                if (type == EdgeType::TREE) {
                    std::cout << "Árvore";
                } else if (type == EdgeType::BACK) {
                    std::cout << "Retorno";
                } else if (type == EdgeType::FORWARD) {
                    std::cout << "Avanço";
                } else {
                    std::cout << "Cruzamento";
                }

                std::cout << "\n";

                for (const auto& edge : edges) {
                    std::cout << "    " << edge.from << " -> " << edge.to << "\n";
                }
            }

            std::cout << "\n";
        }

        else if (opt == 15) {
            graph_ptr->print();

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

        else if (opt == 16) {
            if (graph_ptr != NULL) {
                delete graph_ptr;
            }

            graph_ptr = new DirectedAdjacencyMatrixGraph<char>();
            type = 2;
            is_directed = true;

            choose_file_and_populate_graph(*graph_ptr, true);
            graph_ptr->print();
        }

        else if (opt == 17) {
            if (graph_ptr != NULL) {
                delete graph_ptr;
            }

            graph_ptr = new DirectedIncidenceMatrixGraph<char>();
            type = 3;
            is_directed = true;

            choose_file_and_populate_graph(*graph_ptr, true);
            graph_ptr->print();
        }

        else if (opt == 18) {
            IGraph<char>* other_graph;

            if (type == 2) {
                other_graph = new UndirectedAdjacencyMatrixGraph<char>();
            } else {
                other_graph = new UndirectedIncidenceMatrixGraph<char>();
            }

            graph_ptr->print();

            copy_graph(*graph_ptr, *other_graph);

            std::cout << "Grafo subjacente:\n";

            other_graph->print();

            delete other_graph;
        }

        else if (opt == 19) {
            graph_ptr->print();

            auto bfs_result1 = bfs_digraph(*graph_ptr);

            std::cout << "Componentes da BFS no grafo direcionado:\n";

            for (size_t i = 0; i < bfs_result1.size(); ++i) {
                std::cout << "Componente " << i + 1 << ": ";
                for (const auto& node : bfs_result1[i]) {
                    std::cout << node << " ";
                }
                std::cout << "\n";
            }

            std::cout << "\n";
        }

        else if (opt == 20) {
            graph_ptr->print();

            auto dfs_result = dfs(*graph_ptr);

            for (const auto& [node, time] : dfs_result.discovery) {
                std::cout << "Vértice: " << node << ", Profundidade de Entrada: " << time
                        << ", Profundidade de Saída: " << dfs_result.exit.at(node) << "\n";
            }

            std::cout << "Arestas:\n";
            for (const auto& [type, edges] : dfs_result.edges) {
                std::cout << "Arestas de ";

                if (type == EdgeType::TREE) {
                    std::cout << "Árvore";
                } else if (type == EdgeType::BACK) {
                    std::cout << "Retorno";
                } else if (type == EdgeType::FORWARD) {
                    std::cout << "Avanço";
                } else {
                    std::cout << "Cruzamento";
                }

                std::cout << "\n";

                for (const auto& edge : edges) {
                    std::cout << "    " << edge.from << " -> " << edge.to << "\n";
                }
            }

            std::cout << "\n";
        }
    }
}
