#ifndef APRESENTACAO_TELAS_INSERIR_AUTOR_H
#define APRESENTACAO_TELAS_INSERIR_AUTOR_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/autores/inserir.h"
#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoAutor {
    Campo nome = {
        .nome = "Nome",
        .placeholder = "Nome do(a) Autor(a)",
    };
};

class TelaInserirAutor final : public Tela {
    constexpr static auto BOTAO_INSERIR = "Inserir autor(a)";
    constexpr static auto MSG_SUCESSO = "Autor(a) inserido(a) com sucesso!";

    std::shared_ptr<InserirAutor::UseCase> _caso_de_uso;
    FormularioInsercaoAutor _dados_formulario;

    Component _input_nome;
    Component _botao_inserir;
    Component _formulario;
    Component _layout;

    Element Conteudo() override {
        return vbox({
            hbox(nome(_dados_formulario.nome), _input_nome->Render()),
            filler(),
            hbox({
                _botao_inserir->Render() | color(Color::GreenLight),
                filler(),
            })
        });
    }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoAutor{};
    }

    void _executar_InserirAutorUC() {
        try {
            this->_caso_de_uso->executar({
                .nome = _dados_formulario.nome.valor
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
    explicit TelaInserirAutor()
        : Tela("Formulário para inserção de Autores") {}

    void inicializar() override {
        _caso_de_uso = std::make_shared<InserirAutor::UseCase>(
            _repositorio->getAutores()
        );

        _input_nome = criarInput(_dados_formulario.nome);

        _botao_inserir
                = Button(
                    BOTAO_INSERIR,
                    [this] { this->_executar_InserirAutorUC(); },
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_nome,
            _botao_inserir
        });

        Add(_formulario);
    }
};

#endif //APRESENTACAO_TELAS_INSERIR_AUTOR_H
