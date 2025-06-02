#ifndef APRESENTACAO_TELAS_REALIZAR_EMPRESTIMO_H
#define APRESENTACAO_TELAS_REALIZAR_EMPRESTIMO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/emprestimos/realizar_emprestimo.h"
#include "apresentacao/tui/renderizador.h"
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
    constexpr static auto AVISO_SEM_PESSOA = "Ao menos uma pessoa deve ser cadastrada para realizar empréstimo.";
    constexpr static auto AVISO_SEM_LIVRO = "Ao menos um livro deve ser cadastrado para realizar empréstimo.";
    constexpr static auto BOTAO_EMPRESTAR = "Emprestar";
    constexpr static auto MSG_SUCESSO = "Empréstimo realizado com sucesso!";

    FormularioRealizarEmprestimo _dados_formulario;
    std::shared_ptr<RealizarEmprestimo::UseCase> _caso_de_uso;

    Component _input_id_pessoa;
    Component _input_id_livro;
    Component _botao_emprestar;
    Component _formulario;

    std::string _nome_pessoa;
    std::string _nome_cidade;
    std::string _nome_livro;
    std::string _nome_editora;
    std::string _nome_autor;

    Element Conteudo() override {
        return vbox({
            // Campo de entrada para ID da pessoa
            hbox(
                nome(_dados_formulario.id_pessoa),
                _input_id_pessoa->Render(),
                text('(' + _nome_pessoa + " - " + _nome_cidade + ')') | dim
            ),
            text(this->_deve_mostrar_aviso_pessoa()
                     ? AVISO_SEM_PESSOA
                     : "") | color(Color::Red),

            // Campo de entrada para ID do livro
            hbox(
                nome(_dados_formulario.id_livro),
                _input_id_livro->Render(),
                text('(' + _nome_livro + ", " + _nome_autor + ", " + _nome_editora + ')') | dim
            ),
            text(this->_deve_mostrar_aviso_livro()
                     ? AVISO_SEM_LIVRO
                     : "") | color(Color::Red),

            // Rodapé da tela
            filler(),
            hbox({
                _botao_emprestar->Render() | color(Color::Green),
                filler(),
            })
        });
    }

    bool _deve_mostrar_aviso_pessoa() { return this->_repositorio->getPessoas()->vazia(); }
    bool _deve_mostrar_aviso_livro() { return this->_repositorio->getLivros()->vazia(); }

    void _limpar_formulario() {
        _dados_formulario = FormularioRealizarEmprestimo();
    }

    void _atualizar_nome_pessoa_cidade() {
        try {
            auto pessoa =
                    _repositorio
                    ->getPessoas()
                    ->buscar(_dados_formulario.id_pessoa.valor_numerico());

            if (pessoa.has_value()) {
                auto cidade =
                        _repositorio
                        ->getCidades()
                        ->buscar(pessoa.value()->getIdCidade());
                _nome_pessoa = pessoa.value()->getNome();
                _nome_cidade = cidade.value()->to_string();
            } else {
                _nome_pessoa = "";
                _nome_cidade = "";
            }
        } catch (...) {
            _nome_pessoa = "";
            _nome_cidade = "";
        }
    }

    void _atualizar_nome_livro_editora_autor() {
        try {
            auto livro =
                    _repositorio
                    ->getLivros()
                    ->buscar(_dados_formulario.id_livro.valor_numerico());

            if (livro.has_value()) {
                auto editora =
                        _repositorio
                        ->getEditoras()
                        ->buscar(livro.value()->getIdEditora());
                auto autor =
                        _repositorio
                        ->getAutores()
                        ->buscar(livro.value()->getIdAutor());
                _nome_livro = livro.value()->getNome();
                _nome_editora = editora.value()->getNome();
                _nome_autor = autor.value()->getNome();
            } else {
                _nome_livro = "";
                _nome_editora = "";
                _nome_autor = "";
            }
        } catch (...) {
            _nome_livro = "";
            _nome_editora = "";
            _nome_autor = "";
        }
    }

    void _executar_RealizarEmprestimoUC() {
        try {
            this->_caso_de_uso->executar({
                .id_pessoa = _dados_formulario.id_pessoa.valor_numerico(),
                .id_livro = _dados_formulario.id_livro.valor_numerico()
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
    explicit TelaRealizarEmprestimo()
        : Tela("Formulário para Realizar Empréstimo") {}

    void inicializar() override {
        _caso_de_uso = std::make_shared<RealizarEmprestimo::UseCase>(
            _repositorio->getPessoas(),
            _repositorio->getCidades(),
            _repositorio->getLivros(),
            _repositorio->getEditoras(),
            _repositorio->getAutores(),
            _repositorio->getEmprestimos()
        );

        _nome_pessoa = "";
        _nome_cidade = "";
        _nome_livro = "";
        _nome_editora = "";
        _nome_autor = "";
        _dados_formulario.id_pessoa.ao_enviar = [this] { this->_atualizar_nome_pessoa_cidade(); };
        _dados_formulario.id_livro.ao_enviar = [this] { this->_atualizar_nome_livro_editora_autor(); };

        _input_id_pessoa = criarInput(_dados_formulario.id_pessoa);
        _input_id_livro = criarInput(_dados_formulario.id_livro);

        _botao_emprestar
                = Button(
                    BOTAO_EMPRESTAR,
                    [this] { this->_executar_RealizarEmprestimoUC(); },
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_id_pessoa,
            _input_id_livro,
            _botao_emprestar
        });

        Add(_formulario);
    }
};

#endif //APRESENTACAO_TELAS_REALIZAR_EMPRESTIMO_H
