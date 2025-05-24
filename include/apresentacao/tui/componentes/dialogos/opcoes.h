#ifndef COMPONENTES_DIALOGOS_OPCOES_H
#define COMPONENTES_DIALOGOS_OPCOES_H
#include <functional>
#include <string>

#include "ftxui/dom/elements.hpp"

using namespace ftxui;

using FnFechar = std::function<void()>;
using FnTransformar = std::function<Element(const FnFechar &)>;

struct OpcoesDoDialog {
    // @formatter:off
    static OpcoesDoDialog Padrao(const std::string &titulo,
                                 const Element &conteudo);
    static OpcoesDoDialog Erro(const std::string &mensagem);
    static OpcoesDoDialog Erro(const Element &conteudo);
    // @formatter:on

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

inline OpcoesDoDialog OpcoesDoDialog::Erro(const std::string &mensagem) {
    return Erro(text(mensagem));
}

inline OpcoesDoDialog OpcoesDoDialog::Erro(const Element &conteudo) {
    OpcoesDoDialog estado;
    estado.transformar = [conteudo](const FnFechar &) -> Element {
        return vbox({
                   text("Erro!") | bold | color(Color::Red),
                   separator() | color(Color::Red),
                   conteudo,
               })
               | size(WIDTH, GREATER_THAN, 30)
               | borderStyled(ROUNDED, Color::Red);
    };

    return estado;
}

#endif //COMPONENTES_DIALOGOS_OPCOES_H
