#ifndef APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
#define APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/emprestimos/realizar_devolucao.h"
#include "apresentacao/tui/renderizador.h"
#include "apresentacao/tui/componentes/dialogos/opcoes.h"
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
    constexpr static auto MSG_SUCESSO = "Devolução realizada com sucesso!";

    FormularioRealizarDevolucao _dados_formulario;
    std::shared_ptr<TabelaComponent> _tabela;
    std::shared_ptr<RealizarDevolucao::UseCase> _caso_de_uso;

    Component _input_id_emprestimo;
    Component _botao_devolver;
    Component _formulario;

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
            hbox({
                separatorEmpty(),
                _tabela->Render() | flex,
                separatorEmpty()
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
        _tabela->msg_nenhum_registro = "Aguardando entrada do usuário...";
        _tabela->definirTabelaVazia();
    }

    void _atualizar_informacoes() {
        try {
            auto emprestimo_buscado =
                    _repositorio
                    ->getEmprestimos()
                    ->buscar(_dados_formulario.id_emprestimo.valor_numerico());

            if (emprestimo_buscado.has_value()) {
                const auto &emprestimo = emprestimo_buscado.value();
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

                auto info_livro =
                        std::format("\"{}\", de {} - Editora: {}",
                                    livro->getNome(),
                                    autor->getNome(),
                                    editora->getNome());

                std::vector<Elements> linhas;

                // Formatação condicional para empréstimos em atraso
                Element celula_data_prevista_devolucao;
                auto data_prevista_devolucao_formatada = formatar_data(emprestimo->getDataPrevistaDevolucao());
                time_t agora;
                time(&agora);
                bool devolucao_atrasada =
                        !emprestimo->estaDevolvido() &&
                        emprestimo->getDataPrevistaDevolucao() < agora;

                if (devolucao_atrasada)
                    celula_data_prevista_devolucao =
                            celula(
                                hbox({
                                    text(data_prevista_devolucao_formatada),
                                    text(" (Atrasado)") | color(Color::Red)
                                })
                            );
                else
                    celula_data_prevista_devolucao = celula(data_prevista_devolucao_formatada);

                // Montagem das linhas da tabela
                linhas.emplace_back(Elements{
                    celula(text("Cliente")), celula(pessoa->getNome())
                });
                linhas.emplace_back(Elements{
                    celula(text("Livro")), celula(info_livro)
                });
                linhas.emplace_back(Elements{
                    celula(text("Data do Empréstimo")), celula(formatar_data(emprestimo->getDataEmprestimo()))
                });
                linhas.emplace_back(Elements{
                    celula(text("Data Estimada para Devolução")), celula_data_prevista_devolucao
                });
                linhas.emplace_back(Elements{
                    celula(text("Data da Devolução")), celula(formatar_data(emprestimo->getDataEfetivaDevolucao()))
                });

                this->_tabela->definirDadosTabela(linhas);

                // Estilização de colunas específicas
                this->_tabela->_tabela_base->SelectAll().SeparatorHorizontal(LIGHT);
                this->_tabela->_tabela_base->SelectColumn(0).DecorateCells(color(Color::Cyan));
                this->_tabela->_tabela_base->SelectColumn(1).Decorate(xflex_grow);
            } else {
                this->_limpar_formulario();
            }
        } catch (...) {
            this->_limpar_formulario();
        }
    }

    void _executar_RealizarDevolucaoUC() {
        try {
            this->_caso_de_uso->executar({
                .id_emprestimo = _dados_formulario.id_emprestimo.valor_numerico()
            });

            this->_renderizador->mostrarDialogo(
                OpcoesDoDialog::Sucesso(MSG_SUCESSO)
            );

            this->_limpar_formulario();
            this->_atualizar_informacoes();
        } catch (const std::exception &e) {
            this->_renderizador->mostrarDialogo(
                OpcoesDoDialog::Erro(e.what())
            );
        }
    }

public:
    explicit TelaRealizarDevolucao()
        : Tela("Formulário para Devolução do Empréstimo") {}

    void inicializar() override {
        _caso_de_uso = std::make_shared<RealizarDevolucao::UseCase>(
            _repositorio->getEmprestimos(),
            _repositorio->getLivros()
        );
        _dados_formulario.id_emprestimo.ao_enviar = [this] { this->_atualizar_informacoes(); };

        _input_id_emprestimo = criarInput(_dados_formulario.id_emprestimo);
        _tabela = TabelaConsulta();
        _tabela->aplicar_estilizacao_padrao = false;

        this->_atualizar_informacoes();

        _botao_devolver
                = Button(
                    BOTAO_DEVOLVER,
                    [this] { this->_executar_RealizarDevolucaoUC(); },
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_id_emprestimo,
            _tabela,
            _botao_devolver
        });

        Add(_formulario);
    }
};

#endif //APRESENTACAO_TELAS_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
