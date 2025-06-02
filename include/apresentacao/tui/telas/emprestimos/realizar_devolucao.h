#ifndef APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
#define APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioRealizarDevolucao {
    Campo id_emprestimo = {
        .nome = "Empréstimo",
        .placeholder = "Digite o ID do empréstimo",
        .numerico = true
    };
};

class TelaRealizarDevolucao final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada.")
               | color(Color::Red);
    }

public:
    explicit TelaRealizarDevolucao()
        : Tela("Formulário para Devolução do Empréstimo") {
    }

    void inicializar() override {
    }
};


#endif //APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
