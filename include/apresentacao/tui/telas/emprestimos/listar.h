#ifndef APRESENTACAO_TELAS_EMPRESTIMOS_LISTAR_H
#define APRESENTACAO_TELAS_EMPRESTIMOS_LISTAR_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaListarEmprestimos final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | dim
               | vcenter
               | hcenter;
    }

public:
    explicit TelaListarEmprestimos()
        : Tela("Consulta dos empréstimos registrados") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_EMPRESTIMOS_LISTAR_H
