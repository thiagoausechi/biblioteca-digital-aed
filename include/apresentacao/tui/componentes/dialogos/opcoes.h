#ifndef COMPONENTES_DIALOGOS_OPCOES_H
#define COMPONENTES_DIALOGOS_OPCOES_H
#include <functional>
#include <string>

#include "ftxui/dom/elements.hpp"

using namespace ftxui;

using FnFechar = std::function<void()>;
using FnTransformar = std::function<Element(const FnFechar &)>;

struct OpcoesDoDialog {
    static OpcoesDoDialog Padrao(const std::string &titulo,
                                 const Element &conteudo);

    bool mostrar_dialogo = false; // Reservado para controle do Renderizador
    FnTransformar transformar = [](const FnFechar &) -> Element {
        return text("Renderização do diálogo não definida!")
               | color(Color::Red)
               | borderStyled(ROUNDED, Color::Red);
    };
};

inline OpcoesDoDialog OpcoesDoDialog::Padrao(const std::string &titulo,
                                             const Element &conteudo) {
    OpcoesDoDialog estado;
    estado.transformar = [titulo, conteudo](const FnFechar &) -> Element {
        return vbox({
                   text(titulo) | bold | color(Color::CyanLight),
                   separator(),
                   conteudo,
               })
               | size(WIDTH, GREATER_THAN, 30)
               | border;
    };

    return estado;
}

#endif //COMPONENTES_DIALOGOS_OPCOES_H
