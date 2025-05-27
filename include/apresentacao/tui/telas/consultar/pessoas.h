#ifndef APRESENTACAO_TELAS_CONSULTAR_PESSOAS_H
#define APRESENTACAO_TELAS_CONSULTAR_PESSOAS_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaConsultarPessoas final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | dim
               | vcenter
               | hcenter;
    }

public:
    explicit TelaConsultarPessoas()
        : Tela("Consulta das Pessoas registradas") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_CONSULTAR_PESSOAS_H
