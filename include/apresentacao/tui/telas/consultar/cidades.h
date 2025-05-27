#ifndef APRESENTACAO_TELAS_CONSULTAR_CIDADES_H
#define APRESENTACAO_TELAS_CONSULTAR_CIDADES_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaConsultarCidades final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | dim
               | vcenter
               | hcenter;
    }

public:
    explicit TelaConsultarCidades()
        : Tela("Consulta das Cidades registradas") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_CONSULTAR_CIDADES_H
