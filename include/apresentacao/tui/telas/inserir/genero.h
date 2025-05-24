#ifndef APRESENTACAO_TELAS_INSERIR_GENERO_H
#define APRESENTACAO_TELAS_INSERIR_GENERO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/generos/inserir.h"
#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoGenero {
    Campo descricao = {
        .nome = "Descrição",
        .placeholder = "Descrição/nome do Gênero"
    };
};

class TelaInserirGenero final : public Tela {
    std::shared_ptr<InserirGenero::UseCase> _caso_de_uso;
    FormularioInsercaoGenero _dados_formulario;

    Component _input_descricao;
    Component _botao_inserir;
    Component _formulario;
    Component _layout;

    Element Conteudo() override {
        return vbox({
            hbox(nome(_dados_formulario.descricao), _input_descricao->Render()),
            filler(),
            hbox({
                _botao_inserir->Render() | color(Color::GreenLight),
                filler(),
            })
        });
    }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoGenero{};
    }

    void _executar_InserirGeneroUC() {
        try {
            this->_caso_de_uso->executar({
                .descricao = _dados_formulario.descricao.valor
            });

            this->_renderizador->mostrarDialogo(
                OpcoesDoDialog::Sucesso("Gênero inserido com sucesso!")
            );

            this->_limpar_formulario();
        } catch (const std::exception &e) {
            this->_renderizador->mostrarDialogo(
                OpcoesDoDialog::Erro(e.what())
            );
        }
    }

public:
    explicit TelaInserirGenero()
        : Tela("Formulário para inserção de Gênero") {
    }

    void inicializar() override {
        _caso_de_uso = std::make_shared<InserirGenero::UseCase>(
            _repositorio->getGeneros()
        );

        _input_descricao = criarInput(_dados_formulario.descricao);

        _botao_inserir
                = Button(
                    "Inserir novo gênero",
                    [this] { this->_executar_InserirGeneroUC(); },
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_descricao,
            _botao_inserir
        });

        Add(_formulario);
    }
};

#endif //APRESENTACAO_TELAS_INSERIR_GENERO_H
