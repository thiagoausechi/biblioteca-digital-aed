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
public:
    explicit TelaReserva()
        : Tela("Tela Não Encontrada") {
    }

    Component getComponent() override {
        return Renderer([] {
            return color(Color::Red, text("Nenhuma tela registrada!"));
        });
    }
};

#endif //TELA_RESERVA_H
