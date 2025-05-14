#ifndef MENU_H
#define MENU_H

#include <functional>
#include <iostream>
#include <vector>

#include "terminal_colors.h"

struct ItemDoMenu {
    virtual ~ItemDoMenu() = default;

    virtual void exibir() const {
        throw std::runtime_error("Método não implementado.");
    };
};

struct Opcao final : ItemDoMenu {
    std::string descricao;
    std::function<void()> acao;
    int id = -1;

    explicit Opcao(const std::string &descricao, const std::function<void()> &acao)
        : descricao(descricao)
          , acao(acao) {
    }

    void exibir() const override {
        std::cout << "[" << GREEN << id << RESET << "] " << descricao.c_str() << std::endl;
    };
};

struct Categoria final : ItemDoMenu {
    std::string nome;

    explicit Categoria(const std::string &nome) : nome(nome) {
    }

    void exibir() const override {
        std::cout << "\n" << BLUE << nome.c_str() << RESET << std::endl;
    };
};

// Requisito 8
class Menu {
    int _ultimo_id_opcao = 0;
    std::vector<ItemDoMenu *> _itens_do_menu;

public:
    Menu() {
        this->inserir(new Opcao{"Sair", []() { exit(0); }});
    }

    void inserir(ItemDoMenu *item) {
        // Autoincrementa o “ID” caso seja uma da classe Opção
        if (dynamic_cast<Opcao *>(item) != nullptr) {
            const auto opcao = static_cast<Opcao *>(item);
            opcao->id = this->_ultimo_id_opcao++;
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

            if (opcao_selecionada >= 1 && opcao_selecionada < _ultimo_id_opcao)
                try {
                    const auto opcao = static_cast<Opcao *>(this->_itens_do_menu[opcao_selecionada]);
                    opcao->acao();
                } catch (const std::exception &e) {
                    std::cout << RED << "Erro: " << e.what() << RESET << std::endl;
                }
            else if (opcao_selecionada != 0)
                std::cout << RED << "Opção inválida. Tente novamente." << RESET << std::endl;
            std::cout << BLUE << "* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= *" << RESET << std::endl;
        } while (opcao_selecionada != 0);
    }
};

#endif // MENU_H
