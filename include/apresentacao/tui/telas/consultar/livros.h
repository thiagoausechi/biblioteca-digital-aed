#ifndef APRESENTACAO_TELAS_CONSULTAR_LIVROS_H
#define APRESENTACAO_TELAS_CONSULTAR_LIVROS_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaConsultarLivros final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | dim
               | vcenter
               | hcenter;
    }

public:
    explicit TelaConsultarLivros()
        : Tela("Consulta das Livros registradas") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_CONSULTAR_LIVROS_H
