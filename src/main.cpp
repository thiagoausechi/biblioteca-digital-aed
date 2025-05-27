#include "apresentacao/tui/renderizador.h"
#include "apresentacao/tui/componentes/menu/categoria.h"
#include "apresentacao/tui/componentes/menu/opcao.h"

#include "apresentacao/tui/telas/fabrica.h"
#include "apresentacao/tui/telas/inicio.h"
#include "apresentacao/tui/telas/tela_reserva.h"
#include "apresentacao/tui/telas/consultar/autores.h"
#include "apresentacao/tui/telas/consultar/generos.h"
#include "apresentacao/tui/telas/inserir/genero.h"
#include "apresentacao/tui/telas/inserir/autor.h"
#include "apresentacao/tui/telas/inserir/cidade.h"
#include "apresentacao/tui/telas/inserir/pessoa.h"
#include "apresentacao/tui/telas/inserir/editora.h"
#include "apresentacao/tui/telas/inserir/livro.h"
#include "infraestrutura/fonte_de_dados/persistencia/em_memoria/dados_mockados.h"

#include "infraestrutura/fonte_de_dados/persistencia/em_memoria/tabelas/repositorio.h"

using namespace std;

int main() {
    std::shared_ptr<Renderizador> renderizador = std::make_shared<Renderizador>();
    std::shared_ptr<Repositorio> repositorio = std::make_shared<RepositorioEmMemoria>();
    auto fabrica = std::make_shared<FabricaDeTelas>(repositorio, renderizador);

    MockEmMemoria::inserirDadosMockados(repositorio);

    // Requisito 8
    renderizador->carregarOpcoesDoMenu(Components{
        Opcao("Início", fabrica->criar<TelaInicial>()),
        Renderer([] { return separatorEmpty(); }),

        Categoria("Inserir dados"),
        Opcao("Gêneros", fabrica->criar<TelaInserirGenero>()),
        Opcao("Autores", fabrica->criar<TelaInserirAutor>()),
        Opcao("Cidades", fabrica->criar<TelaInserirCidade>()),
        Opcao("Pessoas", fabrica->criar<TelaInserirPessoa>()),
        Opcao("Editoras", fabrica->criar<TelaInserirEditora>()),
        Opcao("Livros", fabrica->criar<TelaInserirLivro>()),

        Renderer([] { return separatorEmpty(); }),
        Categoria("Consultar dados"),
        Opcao("Gêneros", fabrica->criar<TelaConsultarGeneros>()),
        Opcao("Autores", fabrica->criar<TelaConsultarAutores>()),
        Opcao("Cidades", fabrica->criar<TelaReserva>()),
        Opcao("Pessoas", fabrica->criar<TelaReserva>()),
        Opcao("Editoras", fabrica->criar<TelaReserva>()),
        Opcao("Livros", fabrica->criar<TelaReserva>()),

        Renderer([] { return separatorEmpty(); }),
        Categoria("Empréstimos"),
        Opcao("Realizar empréstimo", fabrica->criar<TelaReserva>()),
        Opcao("Consultar empréstimo", fabrica->criar<TelaReserva>()),
        Opcao("Devolver livro", fabrica->criar<TelaReserva>()),

        Opcao("Listar todos os empréstimos", fabrica->criar<TelaReserva>()),
        Opcao("Listar devoluções em atraso", fabrica->criar<TelaReserva>()),
    });

    renderizador->renderizar();

    return 0;
}
