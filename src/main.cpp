#include <iostream>
#include <clocale>

#include "apresentacao/tui/renderizador.h"
#include "apresentacao/tui/componentes/menu/categoria.h"
#include "apresentacao/tui/componentes/menu/opcao.h"
#include "apresentacao/tui/telas/menu.h"

using namespace std;

// TODO: Limpar código temporário
inline void NAO_IMPLEMENTADO() {
    throw std::runtime_error("Não implementado!");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    auto renderizador = std::make_shared<Renderizador>();

    /**
     * Algumas inserções dependem que outros registros em tabelas
     * diferentes já existam (ex.: uma pessoa deve ter uma cidade associada).
     * Portanto algumas opções devem ficar desabilitadas até que haja
     * ao menos 1 registro na(s) tabela(s) de dependência.
     *
     * TODO: Implementar lógica para habilitar/desabilitar opções
     */
    auto tela_inicial = std::make_shared<TelaMenu>(Components{
        Categoria("Inserir dados"),

        // Arquivos que não dependem de outros registros
        Opcao("Gêneros", &NAO_IMPLEMENTADO),
        Opcao("Autores", &NAO_IMPLEMENTADO),
        Opcao("Cidades", &NAO_IMPLEMENTADO),

        // Arquivos que dependem de outros registros
        Opcao("Pessoas", &NAO_IMPLEMENTADO),
        Opcao("Editoras", &NAO_IMPLEMENTADO),
        Opcao("Livros", &NAO_IMPLEMENTADO),

        Categoria("Consultar dados"),
        Opcao("Gêneros", &NAO_IMPLEMENTADO),
        Opcao("Autores", &NAO_IMPLEMENTADO),
        Opcao("Cidades", &NAO_IMPLEMENTADO),
        Opcao("Pessoas", &NAO_IMPLEMENTADO),
        Opcao("Editoras", &NAO_IMPLEMENTADO),
        Opcao("Livros", &NAO_IMPLEMENTADO),

        Categoria("Empréstimos"),
        Opcao("Realizar empréstimo", &NAO_IMPLEMENTADO),
        Opcao("Consultar empréstimo", &NAO_IMPLEMENTADO),
        Opcao("Devolver livro", &NAO_IMPLEMENTADO),

        Opcao("Listar todos os empréstimos", &NAO_IMPLEMENTADO),
        Opcao("Listar devoluções em atraso", &NAO_IMPLEMENTADO),
    });

    renderizador->navegarPara(tela_inicial);
    renderizador->renderizar();

    return 0;
}
