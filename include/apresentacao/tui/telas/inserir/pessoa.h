#ifndef APRESENTACAO_TELAS_INSERIR_PESSOA_H
#define APRESENTACAO_TELAS_INSERIR_PESSOA_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoPessoa {
    Campo nome = {
        .nome = "Nome",
        .placeholder = "Nome da Pessoa"
    };

    Campo cpf = {
        .nome = "CPF",
        .placeholder = "xxx.xxx.xxx-xx (apenas os dígitos)",
        .numerico = true
    };

    Campo endereco = {
        .nome = "Endereço",
        .placeholder = "Rua Exemplo, 123"
    };

    Campo id_cidade = {
        .nome = "Cidade",
        .placeholder = "Digite o ID da cidade",
        .numerico = true
    };
};

class TelaInserirPessoa final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red);
    }

public:
    explicit TelaInserirPessoa()
        : Tela("Formulário para inserção de Pessoa") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_INSERIR_PESSOA_H
