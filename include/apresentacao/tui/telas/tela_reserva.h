#ifndef TELA_RESERVA_H
#define TELA_RESERVA_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include "tela.h"

using namespace ftxui;

/*
 * Reserva ou "fallback" para quando o Renderizador
 * estiver com a pilha de telas vazia.
 */
class TelaReserva final : public Tela {
    Element OnRender() override {
        return text("Nenhuma tela registrada!")
               | color(Color::Red);
    }

public:
    explicit TelaReserva()
        : Tela("Tela Não Encontrada") {
    }
};

#endif //TELA_RESERVA_H
