#include <iostream>
#include <clocale>

#include "utils/menu.h"

using namespace std;

// TODO: Limpar código temporário
inline void NAO_IMPLEMENTADO() {
    std::cout << RED << "Não implementado!" << RESET << std::endl;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Menu menu;

    /**
     * Algumas inserções dependem que outros registros em tabelas
     * diferentes já existam (ex.: uma pessoa deve ter uma cidade associada).
     * Portanto algumas opções devem ficar desabilitadas até que haja
     * ao menos 1 registro na(s) tabela(s) de dependência.
     *
     * TODO: Implementar lógica para habilitar/desabilitar opções
     */
    menu.inserir(new Categoria{"Inserir dados"});

    // Arquivos que não dependem de outros registros
    menu.inserir(new Opcao{"Gêneros", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Autores", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Cidades", &NAO_IMPLEMENTADO});

    // Arquivos que dependem de outros registros
    menu.inserir(new Opcao{"Pessoas", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Editoras", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Livros", &NAO_IMPLEMENTADO});

    menu.inserir(new Categoria{"Consultar dados"});
    menu.inserir(new Opcao{"Gêneros", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Autores", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Cidades", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Pessoas", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Editoras", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Livros", &NAO_IMPLEMENTADO});

    menu.inserir(new Categoria{"Empréstimos"});
    menu.inserir(new Opcao{"Realizar empréstimo", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Consultar empréstimo", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Devolver livro", &NAO_IMPLEMENTADO});

    menu.inserir(new Opcao{"Listar todos os empréstimos", &NAO_IMPLEMENTADO});
    menu.inserir(new Opcao{"Listar devoluções em atraso", &NAO_IMPLEMENTADO});

    menu.exibir();

    return 0;
}
