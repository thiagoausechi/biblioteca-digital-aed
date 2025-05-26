#ifndef APRESENTACAO_TELAS_INSERIR_PESSOA_H
#define APRESENTACAO_TELAS_INSERIR_PESSOA_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/pessoas/inserir.h"
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
    constexpr static auto AVISO_SEM_CIDADE = "Ao menos uma cidade deve ser cadastrada para inserir uma pessoa.";
    constexpr static auto BOTAO_INSERIR = "Inserir pessoa";
    constexpr static auto MSG_SUCESSO = "Pessoa inserida com sucesso!";

    FormularioInsercaoPessoa _dados_formulario;
    std::shared_ptr<InserirPessoa::UseCase> _caso_de_uso;

    Component _input_nome;
    Component _input_cpf;
    Component _input_endereco;
    Component _input_id_cidade;
    Component _botao_inserir;
    Component _formulario;
    Component _layout;

    std::string _cidade_formatada;

    Element Conteudo() override {
        return vbox({
            hbox(nome(_dados_formulario.nome), _input_nome->Render()),
            hbox(nome(_dados_formulario.cpf), _input_cpf->Render()),
            hbox(nome(_dados_formulario.endereco), _input_endereco->Render()),
            hbox(
                nome(_dados_formulario.id_cidade),
                _input_id_cidade->Render(),
                text('(' + _cidade_formatada + ')') | dim
            ),
            text(this->_deve_mostrar_aviso()
                     ? AVISO_SEM_CIDADE
                     : ""
            ) | color(Color::Red),
            filler(),
            hbox({
                _botao_inserir->Render() | color(Color::GreenLight),
                filler(),
            })
        });
    }

    bool _deve_mostrar_aviso() {
        return this->_repositorio->getCidades()->vazia();
    }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoPessoa{};
    }

    // Requisito 2.2
    void _formatar_cidade() {
        try {
            auto cidade =
                    _repositorio
                    ->getCidades()
                    ->buscar(_dados_formulario.id_cidade.valor_numerico());
            if (cidade.has_value())
                _cidade_formatada = cidade->get()->to_string();
            else
                _cidade_formatada = "";
        } catch (...) {}
    }

    void _executar_InserirPessoaUC() {
        try {
            this->_caso_de_uso->executar({
                .nome = _dados_formulario.nome.valor,
                .cpf = _dados_formulario.cpf.valor,
                .endereco = _dados_formulario.endereco.valor,
                .id_cidade = _dados_formulario.id_cidade.valor_numerico(),
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
    explicit TelaInserirPessoa()
        : Tela("Formulário para inserção de Pessoa") {}

    void inicializar() override {
        _caso_de_uso = std::make_shared<InserirPessoa::UseCase>(
            _repositorio->getPessoas(),
            _repositorio->getCidades()
        );

        _cidade_formatada = "";
        _dados_formulario.id_cidade.ao_enviar = [this] { this->_formatar_cidade(); };

        _input_nome = criarInput(_dados_formulario.nome);
        _input_cpf = criarInput(_dados_formulario.cpf);
        _input_endereco = criarInput(_dados_formulario.endereco);
        _input_id_cidade = criarInput(_dados_formulario.id_cidade);

        _botao_inserir
                = Button(
                    BOTAO_INSERIR,
                    [this] { this->_executar_InserirPessoaUC(); },
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
