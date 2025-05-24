#ifndef APRESENTACAO_TELAS_INSERIR_AUTOR_H
#define APRESENTACAO_TELAS_INSERIR_AUTOR_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoAutor {
    Campo nome = {
        .nome = "Nome",
        .placeholder = "Nome do Autor"
    };
};

class TelaInserirAutor final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red);
    }

public:
    explicit TelaInserirAutor()
        : Tela("Formulário para inserção de Autor") {
    }

    void inicializar() override {
    }
};

#endif //APRESENTACAO_TELAS_INSERIR_AUTOR_H
