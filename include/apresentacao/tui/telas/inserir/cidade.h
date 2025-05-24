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
    constexpr static auto BOTAO_INSERIR = "Inserir cidade";
    FormularioInsercaoCidade _dados_formulario;

    Component _input_nome;
    Component _input_uf;
    Component _botao_inserir;
    Component _formulario;
    Component _layout;

    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red);
    }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoCidade{};
    }

public:
    explicit TelaInserirCidade()
        : Tela("Formulário para inserção de Cidade") {
    }

    void inicializar() override {
        _input_nome = criarInput(_dados_formulario.nome);
        _input_uf = criarInput(_dados_formulario.uf);

        _botao_inserir
                = Button(
                    BOTAO_INSERIR,
                    [] { ; },
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_nome,
            _input_uf,
            _botao_inserir
        });

        Add(_formulario);
    }
};

#endif //APRESENTACAO_TELAS_INSERIR_CIDADE_H
