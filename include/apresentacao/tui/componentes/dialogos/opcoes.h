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
    static OpcoesDoDialog Padrao(const std::string &titulo, const std::string &mensagem);
    static OpcoesDoDialog Padrao(const std::string &titulo, const Element &conteudo);
    static OpcoesDoDialog Erro(const std::string &mensagem);
    static OpcoesDoDialog Erro(const Element &conteudo);
    static OpcoesDoDialog Aviso(const std::string &mensagem);
    static OpcoesDoDialog Aviso(const Element &conteudo);
    static OpcoesDoDialog Sucesso(const std::string &mensagem);
    static OpcoesDoDialog Sucesso(const Element &conteudo);
    // @formatter:on

    bool mostrar_dialogo = false; // Reservado para controle do Renderizador
    FnTransformar transformar = [](const FnFechar &) -> Element {
        return text("Renderização do diálogo não definida!")
               | color(Color::Red)
               | borderStyled(ROUNDED, Color::Red);
    };
};

inline Element TransformadorPadraoDialogo(
    const Element &titulo,
    const Element &conteudo,
    Color cor_tema = Color::White
) {
    return vbox({
               titulo | bold,
               separator() | color(cor_tema),
               conteudo,
               separator() | color(cor_tema),
               text("Pressione [ESC] para sair") | dim
           })
           | size(WIDTH, GREATER_THAN, 30)
           | borderStyled(ROUNDED, cor_tema);
}

inline OpcoesDoDialog OpcoesDoDialog::Padrao(const std::string &titulo, const std::string &mensagem) {
    return Padrao(titulo, text(mensagem));
}

inline OpcoesDoDialog OpcoesDoDialog::Padrao(const std::string &titulo, const Element &conteudo) {
    OpcoesDoDialog estado;
    estado.transformar = [titulo, conteudo](const FnFechar &) -> Element {
        return TransformadorPadraoDialogo(text(titulo) | color(Color::CyanLight), conteudo);
    };

    return estado;
}

inline OpcoesDoDialog OpcoesDoDialog::Erro(const std::string &mensagem) {
    return Erro(text(mensagem));
}

inline OpcoesDoDialog OpcoesDoDialog::Erro(const Element &conteudo) {
    OpcoesDoDialog estado;
    estado.transformar = [conteudo](const FnFechar &) -> Element {
        Color cor_tema = Color::Red;
        return TransformadorPadraoDialogo(text("Erro!") | color(cor_tema), conteudo, cor_tema);
    };

    return estado;
}

inline OpcoesDoDialog OpcoesDoDialog::Aviso(const std::string &mensagem) {
    return Aviso(text(mensagem));
}

inline OpcoesDoDialog OpcoesDoDialog::Aviso(const Element &conteudo) {
    OpcoesDoDialog estado;
    estado.transformar = [conteudo](const FnFechar &) -> Element {
        Color cor_tema = Color::YellowLight;
        return TransformadorPadraoDialogo(text("Atenção!") | color(cor_tema), conteudo, cor_tema);
    };

    return estado;
}

inline OpcoesDoDialog OpcoesDoDialog::Sucesso(const std::string &mensagem) {
    return Sucesso(text(mensagem));
}

inline OpcoesDoDialog OpcoesDoDialog::Sucesso(const Element &conteudo) {
    OpcoesDoDialog estado;
    estado.transformar = [conteudo](const FnFechar &) -> Element {
        Color cor_tema = Color::GreenLight;
        return TransformadorPadraoDialogo(text("Sucesso!") | color(cor_tema), conteudo, cor_tema);
    };

    return estado;
}

#endif //COMPONENTES_DIALOGOS_OPCOES_H
