#ifndef APRESENTACAO_TELAS_INSERIR_CIDADE_H
#define APRESENTACAO_TELAS_INSERIR_CIDADE_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/cidades/inserir.h"
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
    constexpr static auto MSG_SUCESSO = "Cidade inserida com sucesso!";

    FormularioInsercaoCidade _dados_formulario;
    std::shared_ptr<InserirCidade::UseCase> _caso_de_uso;

    Component _input_nome;
    Component _input_uf;
    Component _botao_inserir;
    Component _formulario;

    Element Conteudo() override {
        return vbox({
            hbox(nome(_dados_formulario.nome), _input_nome->Render()),
            hbox(nome(_dados_formulario.uf), _input_uf->Render()),
            filler(),
            hbox({
                _botao_inserir->Render() | color(Color::GreenLight),
                filler(),
            })
        });
    }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoCidade{};
    }

    void _executar_InserirCidadeUC() {
        try {
            this->_caso_de_uso->executar({
                .nome = _dados_formulario.nome.valor,
                .uf = _dados_formulario.uf.valor,
            });

            this->_renderizador->mostrarDialogo(
                OpcoesDoDialog::Sucesso(MSG_SUCESSO)
            );

            this->_limpar_formulario();
        } catch (const std::exception &e) {
            this->_renderizador->mostrarDialogo(
                OpcoesDoDialog::Erro(e.what())
            );
        }
    }

public:
    explicit TelaInserirCidade()
        : Tela("Formulário para inserção de Cidade") {
    }

    void inicializar() override {
        _caso_de_uso = std::make_shared<InserirCidade::UseCase>(
            _repositorio->getCidades()
        );

        _input_nome = criarInput(_dados_formulario.nome);
        _input_uf = criarInput(_dados_formulario.uf);

        _botao_inserir
                = Button(
                    BOTAO_INSERIR,
                    [this] { this->_executar_InserirCidadeUC(); },
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
