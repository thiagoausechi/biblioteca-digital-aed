#include <iostream>
#include <clocale>

#include "apresentacao/tui/renderizador.h"
#include "utils/menu.h"

using namespace std;

// TODO: Limpar código temporário
inline void NAO_IMPLEMENTADO() {
    throw std::runtime_error("Não implementado!");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    auto renderizador = std::make_shared<Renderizador>();
    renderizador->renderizar();

    menu::Menu menu;

    /**
     * Algumas inserções dependem que outros registros em tabelas
     * diferentes já existam (ex.: uma pessoa deve ter uma cidade associada).
     * Portanto algumas opções devem ficar desabilitadas até que haja
     * ao menos 1 registro na(s) tabela(s) de dependência.
     *
     * TODO: Implementar lógica para habilitar/desabilitar opções
     */
    menu.inserir(new menu::Categoria{"Inserir dados"});

    // Arquivos que não dependem de outros registros
    menu.inserir(new menu::Opcao{"Gêneros", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Autores", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Cidades", &NAO_IMPLEMENTADO});

    // Arquivos que dependem de outros registros
    menu.inserir(new menu::Opcao{"Pessoas", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Editoras", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Livros", &NAO_IMPLEMENTADO});

    menu.inserir(new menu::Categoria{"Consultar dados"});
    menu.inserir(new menu::Opcao{"Gêneros", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Autores", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Cidades", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Pessoas", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Editoras", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Livros", &NAO_IMPLEMENTADO});

    menu.inserir(new menu::Categoria{"Empréstimos"});
    menu.inserir(new menu::Opcao{"Realizar empréstimo", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Consultar empréstimo", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Devolver livro", &NAO_IMPLEMENTADO});

    menu.inserir(new menu::Opcao{"Listar todos os empréstimos", &NAO_IMPLEMENTADO});
    menu.inserir(new menu::Opcao{"Listar devoluções em atraso", &NAO_IMPLEMENTADO});

    // menu.exibir(); FIXME: Mover responsabilidade de exibição para a classe TelaMenu
    // Temporariamente o menu não está sendo exibido

    return 0;
}
