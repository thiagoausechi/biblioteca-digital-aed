#ifndef MENU_H
#define MENU_H

#include <functional>
#include <iostream>
#include <vector>

#include "terminal_colors.h"

// Requisito 8
class Menu {
    std::vector<std::pair<std::string, std::function<void()>>> _opcoes_do_menu;

public:
    Menu() {
        this->adicionarOpcao("Sair", [] { ; });
    }

    void adicionarOpcao(const std::string &descricao, const std::function<void()> &acao) {
        if (descricao.empty())
            throw std::invalid_argument("Descrição da opção não pode ser vazia.");
        if (acao == nullptr)
            throw std::invalid_argument("Ação da opção não pode ser nula.");

        _opcoes_do_menu.emplace_back(descricao, acao);
    }

    void exibir() const {
        int opcao_selecionada;

        do {
            for (size_t i = 0; i < this->_opcoes_do_menu.size(); ++i)
                std::cout << "[" << GREEN << i << RESET << "] " << this->_opcoes_do_menu[i].first.c_str() << std::endl;
            std::cout << "\nDigite o número da opção que você deseja executar: ";
            std::cin >> opcao_selecionada;

            if (opcao_selecionada >= 1 && opcao_selecionada < this->_opcoes_do_menu.size())
                try {
                    this->_opcoes_do_menu[opcao_selecionada].second();
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
