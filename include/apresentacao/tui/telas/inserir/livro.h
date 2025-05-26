#ifndef APRESENTACAO_TELAS_INSERIR_LIVRO_H
#define APRESENTACAO_TELAS_INSERIR_LIVRO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoLivro {
    Campo nome = {
        .nome = "Nome",
        .placeholder = "Nome do Livro"
    };

    Campo id_editora = {
        .nome = "Editora",
        .placeholder = "Digite o ID da editora",
        .numerico = true
    };

    Campo id_autor = {
        .nome = "Autor(a)",
        .placeholder = "Digite o ID do(a) autor(a)",
        .numerico = true
    };

    Campo id_genero = {
        .nome = "Gênero",
        .placeholder = "Digite o ID do gênero",
        .numerico = true
    };
};

class TelaInserirLivro final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red);
    }

public:
    explicit TelaInserirLivro()
        : Tela("Formulário para inserção de Livro") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_INSERIR_LIVRO_H
