#include "apresentacao/tui/renderizador.h"
#include "apresentacao/tui/componentes/menu/categoria.h"
#include "apresentacao/tui/componentes/menu/opcao.h"
#include "apresentacao/tui/telas/fabrica.h"
#include "apresentacao/tui/telas/inicio.h"
#include "apresentacao/tui/telas/tela_reserva.h"
#include "apresentacao/tui/telas/inserir/genero.h"

using namespace std;

int main() {
    std::shared_ptr<Renderizador> renderizador;
    std::shared_ptr<Repositorio> repositorio = nullptr; // TODO: Implementar Repositório
    auto fabrica = std::make_shared<FabricaDeTelas>(repositorio, renderizador);

    renderizador = std::make_shared<Renderizador>(Components{
        Opcao("Início", fabrica->criar<TelaInicial>()),
        Renderer([] { return separatorEmpty(); }),

        Categoria("Inserir dados"),
        Opcao("Gêneros", fabrica->criar<TelaInserirGenero>()),
        Opcao("Autores", fabrica->criar<TelaReserva>()),
        Opcao("Cidades", fabrica->criar<TelaReserva>()),
        Opcao("Pessoas", fabrica->criar<TelaReserva>()),
        Opcao("Editoras", fabrica->criar<TelaReserva>()),
        Opcao("Livros", fabrica->criar<TelaReserva>()),

        Renderer([] { return separatorEmpty(); }),
        Categoria("Consultar dados"),
        Opcao("Gêneros", fabrica->criar<TelaReserva>()),
        Opcao("Autores", fabrica->criar<TelaReserva>()),
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
