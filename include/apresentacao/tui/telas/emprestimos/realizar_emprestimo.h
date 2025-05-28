#ifndef APRESENTACAO_TELAS_REALIZAR_EMPRESTIMO_H
#define APRESENTACAO_TELAS_REALIZAR_EMPRESTIMO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioRealizarEmprestimo {
    Campo id_pessoa = {
        .nome = "Pessoa",
        .placeholder = "Digite o ID da pessoa",
        .numerico = true
    };

    Campo id_livro = {
        .nome = "Livro",
        .placeholder = "Digite o ID do livro",
        .numerico = true
    };
};

class TelaRealizarEmprestimo final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada.")
               | color(Color::Red);
    }

public:
    explicit TelaRealizarEmprestimo()
        : Tela("Formulário para Realizar Empréstimo") {
    }

    void inicializar() override {
    }
};

#endif //APRESENTACAO_TELAS_REALIZAR_EMPRESTIMO_H
