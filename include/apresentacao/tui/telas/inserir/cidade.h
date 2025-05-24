#ifndef APRESENTACAO_TELAS_INSERIR_CIDADE_H
#define APRESENTACAO_TELAS_INSERIR_CIDADE_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoCidade {
    Campo nome = {
        .nome = "Nome",
        .placeholder = "Nome da Cidade"
    };

    Campo uf = {
        .nome = "UF",
        .placeholder = "Sigla da Unidade Federativa"
    };
};

class TelaInserirCidade final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red);
    }

public:
    explicit TelaInserirCidade()
        : Tela("Formulário para inserção de Cidade") {
    }

    void inicializar() override {
    }
};

#endif //APRESENTACAO_TELAS_INSERIR_CIDADE_H
