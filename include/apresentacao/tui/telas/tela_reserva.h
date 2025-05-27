#ifndef APRESENTACAO_TELAS_TELA_RESERVA_H
#define APRESENTACAO_TELAS_TELA_RESERVA_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include "tela.h"

using namespace ftxui;

/*
 * Reserva ou "fallback" para quando alguma tela
 * ainda não tiver sido implementada.
 */
class TelaReserva final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red)
               | vcenter
               | hcenter;
    }

public:
    explicit TelaReserva()
        : Tela("Tela Não Implementada") {
    }

    void inicializar() override {
    }
};

#endif //APRESENTACAO_TELAS_TELA_RESERVA_H
