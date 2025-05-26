#ifndef APRESENTACAO_TELAS_INSERIR_EDITORA_H
#define APRESENTACAO_TELAS_INSERIR_EDITORA_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoEditora {
    Campo nome = {
        .nome = "Nome",
        .placeholder = "Nome da Editora"
    };

    Campo id_cidade = {
        .nome = "Cidade",
        .placeholder = "Digite o ID da cidade",
        .numerico = true
    };
};

class TelaInserirEditora final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red);
    }

public:
    explicit TelaInserirEditora()
        : Tela("Formulário para inserção de Editora`") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_INSERIR_EDITORA_H
