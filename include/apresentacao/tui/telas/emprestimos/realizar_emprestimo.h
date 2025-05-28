#ifndef APRESENTACAO_TELAS_REALIZAR_EMPRESTIMO_H
#define APRESENTACAO_TELAS_REALIZAR_EMPRESTIMO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

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
    constexpr static auto BOTAO_EMPRESTAR = "Emprestar";

    FormularioRealizarEmprestimo _dados_formulario;

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
        return text("Esta tela ainda não foi implementada.")
               | color(Color::Red);
    }

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

public:
    explicit TelaRealizarEmprestimo()
        : Tela("Formulário para Realizar Empréstimo") {
    }

    void inicializar() override {
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
                    [] {
                    },
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
