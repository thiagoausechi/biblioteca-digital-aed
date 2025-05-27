#ifndef APRESENTACAO_TELAS_CONSULTAR_EDITORAS_H
#define APRESENTACAO_TELAS_CONSULTAR_EDITORAS_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaConsultarEditoras final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | dim
               | vcenter
               | hcenter;
    }

public:
    explicit TelaConsultarEditoras()
        : Tela("Consulta das Editoras registradas") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_CONSULTAR_EDITORAS_H
