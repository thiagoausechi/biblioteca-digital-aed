#ifndef APRESENTACAO_TELAS_CONSULTAR_AUTORES_H
#define APRESENTACAO_TELAS_CONSULTAR_AUTORES_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaConsultarAutores final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | dim
               | vcenter
               | hcenter;
    }

public:
    explicit TelaConsultarAutores()
        : Tela("Consulta dos Autores registrados") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_CONSULTAR_AUTORES_H
