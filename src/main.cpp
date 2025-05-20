#include "apresentacao/tui/renderizador.h"
#include "apresentacao/tui/componentes/menu/categoria.h"
#include "apresentacao/tui/componentes/menu/opcao.h"
#include "apresentacao/tui/telas/inicio.h"
#include "apresentacao/tui/telas/tela_reserva.h"
#include "apresentacao/tui/telas/inserir/genero.h"

using namespace std;

int main() {
    auto renderizador = std::make_shared<Renderizador>(Components{
        Opcao("Início", Make<TelaInicial>()),
        Renderer([] { return separatorEmpty(); }),

        Categoria("Inserir dados"),
        Opcao("Gêneros", Make<TelaInserirGenero>()),
        Opcao("Autores", Make<TelaReserva>()),
        Opcao("Cidades", Make<TelaReserva>()),
        Opcao("Pessoas", Make<TelaReserva>()),
        Opcao("Editoras", Make<TelaReserva>()),
        Opcao("Livros", Make<TelaReserva>()),

        Renderer([] { return separatorEmpty(); }),
        Categoria("Consultar dados"),
        Opcao("Gêneros", Make<TelaReserva>()),
        Opcao("Autores", Make<TelaReserva>()),
        Opcao("Cidades", Make<TelaReserva>()),
        Opcao("Pessoas", Make<TelaReserva>()),
        Opcao("Editoras", Make<TelaReserva>()),
        Opcao("Livros", Make<TelaReserva>()),

        Renderer([] { return separatorEmpty(); }),
        Categoria("Empréstimos"),
        Opcao("Realizar empréstimo", Make<TelaReserva>()),
        Opcao("Consultar empréstimo", Make<TelaReserva>()),
        Opcao("Devolver livro", Make<TelaReserva>()),

        Opcao("Listar todos os empréstimos", Make<TelaReserva>()),
        Opcao("Listar devoluções em atraso", Make<TelaReserva>()),
    });

    renderizador->renderizar();

    return 0;
}
