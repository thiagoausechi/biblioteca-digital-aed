#ifndef MENU_H
#define MENU_H

#include <functional>
#include <iostream>
#include <utility>
#include <vector>

#include "terminal_colors.h"
#include "terminal_header.h"

namespace menu {
    struct ItemDoMenu {
        virtual ~ItemDoMenu() = default;

        virtual void exibir() const {
            throw std::runtime_error("Método não implementado.");
        }
    };

    struct Opcao final : ItemDoMenu {
        std::string descricao;
        std::function<void()> acao;
        int id = -1;

        explicit Opcao(std::string descricao, const std::function<void()> &acao)
            : descricao(std::move(descricao))
              , acao(acao) {
        }

        void exibir() const override {
            std::cout << "  [" << GREEN << id << RESET << "] " << descricao.c_str() << std::endl;
        }

        void executar() {
            std::cout << cabecalho(this->descricao) << std::endl;
            this->acao();
        }
    };

    struct Categoria final : ItemDoMenu {
        std::string nome;

        explicit Categoria(std::string nome) : nome(std::move(nome)) { ; }

        void exibir() const override {
            std::cout << "\n" << BOLD << BLUE << nome.c_str() << RESET << std::endl;
        }
    };

    struct MensagemDeBoasVindas final : ItemDoMenu {
        void exibir() const override {
            std::cout << cabecalho("Bem-vindo(a)!") << std::endl;
        }
    };

    // Requisito 8
    class Menu {
        int _ultimo_id_opcao = 0;

        // Nem sempre o ID da opção é o mesmo que o índice do vetor
        std::unordered_map<int, unsigned long> _mapa_indice_opcoes;
        std::vector<ItemDoMenu *> _itens_do_menu;

    public:
        Menu() {
            this->inserir(new MensagemDeBoasVindas());
            this->inserir(new Opcao{"Sair", [] { ; }});
        }

        void inserir(ItemDoMenu *item) {
            // Autoincrementa o “ID” caso seja uma da classe Opção
            if (dynamic_cast<Opcao *>(item) != nullptr) {
                const auto opcao = dynamic_cast<Opcao *>(item);
                opcao->id = this->_ultimo_id_opcao++;

                // Associa o ID da opção ao índice no vetor _itens_do_menu
                this->_mapa_indice_opcoes[opcao->id] = this->_itens_do_menu.size();
            }

            _itens_do_menu.emplace_back(item);
        }

        void exibir() const {
            int opcao_selecionada;

            do {
                for (const auto item: this->_itens_do_menu)
                    item->exibir();

                std::cout << "\nDigite o número da opção que você deseja executar: ";
                std::cin >> opcao_selecionada;

                limpar_terminal();
                if (opcao_selecionada >= 1 && opcao_selecionada < _ultimo_id_opcao)
                    try {
                        const auto indice_opcao = this->_mapa_indice_opcoes.at(opcao_selecionada);
                        const auto opcao = dynamic_cast<Opcao *>(this->_itens_do_menu[indice_opcao]);
                        opcao->executar();
                    } catch (const std::exception &e) {
                        std::cout << RED << "Erro: " << e.what() << RESET << std::endl;
                    }
                else if (opcao_selecionada != 0)
                    std::cout << RED << "Opção inválida. Tente novamente." << RESET << std::endl;
            } while (opcao_selecionada != 0);

            std::cout << cabecalho("Até mais!") << std::endl;
        }

        static void limpar_terminal() {
            // @formatter:off
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            // @formatter:on
        }
    };
}

#endif // MENU_H
