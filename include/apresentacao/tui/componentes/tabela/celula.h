#ifndef APRESENTACAO_COMPONENTES_TABELA_CELULA_H
#define APRESENTACAO_COMPONENTES_TABELA_CELULA_H
#include <ftxui/dom/elements.hpp>
#include <utility>

using namespace ftxui;

inline Element celula(Element conteudo) {
    return hbox({
        separatorEmpty(),
        std::move(conteudo) | xflex,
        separatorEmpty(),
    });
}

inline Element celula(const std::string &conteudo) {
    return celula(paragraphAlignLeft(conteudo));
}

#endif //APRESENTACAO_COMPONENTES_TABELA_CELULA_H
