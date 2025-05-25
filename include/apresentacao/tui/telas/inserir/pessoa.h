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
    constexpr static auto BOTAO_INSERIR = "Inserir pessoa";

    FormularioInsercaoPessoa _dados_formulario;

    Component _input_nome;
    Component _input_cpf;
    Component _input_endereco;
    Component _input_id_cidade;
    Component _botao_inserir;
    Component _formulario;
    Component _layout;

    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red);
    }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoPessoa{};
    }

public:
    explicit TelaInserirPessoa()
        : Tela("Formulário para inserção de Pessoa") {}

    void inicializar() override {
        _input_nome = criarInput(_dados_formulario.nome);
        _input_cpf = criarInput(_dados_formulario.cpf);
        _input_endereco = criarInput(_dados_formulario.endereco);
        _input_id_cidade = criarInput(_dados_formulario.id_cidade);

        _botao_inserir
                = Button(
                    BOTAO_INSERIR,
                    [] { ; },
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_nome,
            _input_cpf,
            _input_endereco,
            _input_id_cidade,
            _botao_inserir
        });

        Add(_formulario);
    }
};

#endif //APRESENTACAO_TELAS_INSERIR_PESSOA_H
