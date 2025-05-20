#ifndef TELA_INSERIR_GENERO_H
#define TELA_INSERIR_GENERO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaInserirGenero final : public Tela {
    Element OnRender() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::YellowLight);
    }

public:
    explicit TelaInserirGenero()
        : Tela("Formulário para inserção de Gênero") {
    }
};

#endif //TELA_INSERIR_GENERO_H
