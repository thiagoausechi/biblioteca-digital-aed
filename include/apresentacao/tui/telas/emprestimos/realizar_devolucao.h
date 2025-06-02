#ifndef APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
#define APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"
#include "utils/date.h"

using namespace ftxui;

struct FormularioRealizarDevolucao {
    Campo id_emprestimo = {
        .nome = "Empréstimo",
        .placeholder = "Digite o ID do empréstimo",
        .numerico = true
    };
};

class TelaRealizarDevolucao final : public Tela {
    constexpr static auto AVISO_SEM_EMPRESTIMO = "Deve ter ao menos um empréstimo para realizar devolução.";
    constexpr static auto BOTAO_DEVOLVER = "Devolver";

    FormularioRealizarDevolucao _dados_formulario;

    Component _input_id_emprestimo;
    Component _botao_devolver;
    Component _formulario;

    bool _informacoes_carregadas;

    std::string _nome_pessoa;
    std::string _info_livro;
    std::string _data_emprestimo;
    std::string _data_devolucao;

    Element Conteudo() override {
        return vbox({
            // Campo de entrada para ID do empréstimo
            hbox(
                nome(_dados_formulario.id_emprestimo),
                _input_id_emprestimo->Render()
            ),
            text(this->_deve_mostrar_aviso_emprestimo()
                     ? AVISO_SEM_EMPRESTIMO
                     : "") | color(Color::Red),

            // Informações
            separatorEmpty(),
            !_informacoes_carregadas
                ? text("Aguardando entrada do usuário...")
                : vbox({
                    text("Cliente: " + _nome_pessoa),
                    text("Livro: " + _info_livro),
                    text("Data Empréstimo: " + _data_emprestimo),
                    text("Data Devolução: " + _data_devolucao)
                }),

            // Rodapé da tela
            filler(),
            hbox({
                _botao_devolver->Render() | color(Color::Green),
                filler(),
            })
        });
    }

    bool _deve_mostrar_aviso_emprestimo() { return this->_repositorio->getEmprestimos()->vazia(); }

    void _limpar_formulario() {
        _dados_formulario = FormularioRealizarDevolucao();
    }

    void _limpar_informacoes() {
        _informacoes_carregadas = false;
        _nome_pessoa = "";
        _info_livro = "";
        _data_emprestimo = "";
        _data_devolucao = "";
    }

    void _atualizar_informacoes() {
        try {
            auto emprestimo_buscado =
                    _repositorio
                    ->getEmprestimos()
                    ->buscar(_dados_formulario.id_emprestimo.valor_numerico());

            if (emprestimo_buscado.has_value()) {
                auto emprestimo = emprestimo_buscado.value();
                auto pessoa =
                        _repositorio
                        ->getPessoas()
                        ->buscar(emprestimo->getIdPessoa())
                        .value();
                auto livro =
                        _repositorio
                        ->getLivros()
                        ->buscar(emprestimo->getIdLivro())
                        .value();
                auto editora =
                        _repositorio
                        ->getEditoras()
                        ->buscar(livro->getIdEditora())
                        .value();
                auto autor =
                        _repositorio
                        ->getAutores()
                        ->buscar(livro->getIdAutor())
                        .value();

                _informacoes_carregadas = true;
                _nome_pessoa = pessoa->getNome();
                _info_livro =
                        std::format("\"{}\", de {} - Editora: {}",
                                    livro->getNome(),
                                    autor->getNome(),
                                    editora->getNome());
                _data_devolucao = formatar_data(emprestimo->getDataEfetivaDevolucao());
                _data_emprestimo = formatar_data(emprestimo->getDataEmprestimo());
            } else {
                this->_limpar_informacoes();
            }
        } catch (...) {
            this->_limpar_informacoes();
        }
    }

public:
    explicit TelaRealizarDevolucao()
        : Tela("Formulário para Devolução do Empréstimo") {
    }

    void inicializar() override {
        this->_limpar_informacoes();
        _dados_formulario.id_emprestimo.ao_enviar = [this] { this->_atualizar_informacoes(); };

        _input_id_emprestimo = criarInput(_dados_formulario.id_emprestimo);

        _botao_devolver
                = Button(
                    BOTAO_DEVOLVER,
                    [] {
                    },
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_id_emprestimo,
            _botao_devolver
        });

        Add(_formulario);
    }
};


#endif //APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
