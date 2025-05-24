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

#endif //COMPONENTES_DIALOGOS_OPCOES_H
