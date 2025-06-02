#ifndef APRESENTACAO_TELAS_EMPRESTIMOS_LISTAR_H
#define APRESENTACAO_TELAS_EMPRESTIMOS_LISTAR_H
#include <iomanip>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/livros/listar_emprestados.h"
#include "apresentacao/tui/componentes/tabela/celula.h"
#include "apresentacao/tui/telas/tela.h"
#include "apresentacao/tui/componentes/tabela/tabela.h"

using namespace ftxui;

class TelaListarEmprestimos final : public Tela {
    std::shared_ptr<TabelaComponent> _tabela;
    std::shared_ptr<ListarLivrosEmprestados::UseCase> _caso_de_uso;

    int _quantidade_emprestados;
    int _quantidade_disponiveis;

    Element Conteudo() override {
        return hbox({
            separatorEmpty(),
            vbox({
                _tabela->Render() | xflex,
                hbox({
                    text("Emprestados: " + std::to_string(_quantidade_emprestados))
                    | center
                    | xflex_grow,
                    separator(),
                    text("Disponíveis: " + std::to_string(_quantidade_disponiveis))
                    | center
                    | xflex_grow,
                }) | borderStyled(LIGHT) | dim
            }) | flex,
            separatorEmpty(),
        });
    }

    void _carregarTabela() {
        auto resposta = _caso_de_uso->executar();

        this->_quantidade_disponiveis = resposta.quantidade_disponiveis;
        this->_quantidade_emprestados = resposta.quantidade_emprestados;

        if (resposta.quantidade_emprestados == 0) {
            _tabela->definirTabelaVazia(Emprestimo::NOME_CLASSE);
            return;
        }

        std::vector<Elements> linhas;
        std::ostringstream id_formatado;

        // Cabeçalho da Tabela
        linhas.emplace_back(Elements{
            celula(text("ID")),
            celula(text("Nome do Livro"))
        });

        // Dados da Tabela
        for (const auto &[id, nome]: resposta.livros_emprestados) {
            id_formatado << std::setfill('0') << std::setw(2) << id;

            linhas.emplace_back(Elements{
                celula(text(id_formatado.str())),
                celula(nome)
            });

            id_formatado.str("");
            id_formatado.clear();
        }

        this->_tabela->definirDadosTabela(linhas);

        // Estilização de colunas específicas
        this->_tabela->_tabela_base->SelectColumn(1).Decorate(xflex_grow);
    }

public:
    explicit TelaListarEmprestimos()
        : Tela("Consulta dos empréstimos registrados") {}

    void inicializar() override {
        _caso_de_uso = std::make_shared<ListarLivrosEmprestados::UseCase>(
            _repositorio->getLivros()
        );

        _tabela = TabelaConsulta();
        Add(_tabela);

        _quantidade_emprestados = 0;
        _quantidade_disponiveis = 0;

        this->_carregarTabela();
    }

    void ao_entrar() override { this->_carregarTabela(); }
};

#endif //APRESENTACAO_TELAS_EMPRESTIMOS_LISTAR_H
