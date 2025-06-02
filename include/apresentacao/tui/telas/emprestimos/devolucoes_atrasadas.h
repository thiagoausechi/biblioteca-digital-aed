#ifndef APRESENTACAO_TELAS_DEVOLUCOES_ATRASADAS_H
#define APRESENTACAO_TELAS_DEVOLUCOES_ATRASADAS_H
#include<ftxui/dom/elements.hpp>
#include<ftxui/component/component.hpp>

#include"apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaListarDevolucoesAtrasadas final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | dim
               | vcenter
               | hcenter;
    }

public:
    explicit TelaListarDevolucoesAtrasadas()
        : Tela("Consulta das devoluções em atraso") {
    }

    void inicializar() override {
    }
};

#endif //APRESENTACAO_TELAS_DEVOLUCOES_ATRASADAS_H
