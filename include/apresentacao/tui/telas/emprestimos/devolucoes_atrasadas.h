#ifndef APRESENTACAO_TELAS_DEVOLUCOES_ATRASADAS_H
#define APRESENTACAO_TELAS_DEVOLUCOES_ATRASADAS_H
#include<iomanip>
#include<ftxui/dom/elements.hpp>
#include<ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/emprestimos/listar_devolucao_atrasada.h"
#include "apresentacao/tui/componentes/tabela/celula.h"
#include "apresentacao/tui/componentes/tabela/tabela.h"
#include"apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaListarDevolucoesAtrasadas final : public Tela {
    std::shared_ptr<TabelaComponent> _tabela;
    std::shared_ptr<ListarDevolucaoAtrasada::UseCase> _caso_de_uso;

    Element Conteudo() override {
        return hbox({
            separatorEmpty(),
            _tabela->Render() | flex,
            separatorEmpty(),
        });
    }

    void _carregarTabela() {
        auto resposta = _caso_de_uso->executar();

        if (resposta.empty()) {
            _tabela->definirTabelaVazia("Devoluções Atrasadas");
            return;
        }

        std::vector<Elements> linhas;
        std::ostringstream id_formatado;

        // Cabeçalho da Tabela
        linhas.emplace_back(Elements{
            celula(text("ID")),
            celula(text("Informações do Livro")),
            celula(text("Data da Devolução")),
            celula(text("Dias em Atraso")),
        });

        for (const auto livro: resposta) {
            id_formatado << std::setfill('0') << std::setw(2) << livro.id_livro;
            auto info_livro = std::format("\"{}\", de {} - Editora: {}",
                                          livro.nome_livro,
                                          livro.nome_autor,
                                          livro.nome_editora);

            linhas.emplace_back(Elements{
                celula(text(id_formatado.str())),
                celula(info_livro),
                celula(text(livro.data_prevista_devolucao_formatada)),
                celula(text(std::to_string(livro.dias_atraso)))
            });

            id_formatado.str("");
            id_formatado.clear();
        }

        this->_tabela->definirDadosTabela(linhas);

        // Estilização de Colunas Específicas
        this->_tabela->_tabela_base->SelectColumn(1).Decorate(xflex_grow);
        this->_tabela->_tabela_base->SelectColumns(2, -1).Decorate(xflex);
    }

public:
    explicit TelaListarDevolucoesAtrasadas()
        : Tela("Consulta das devoluções em atraso") {
    }

    void inicializar() override {
        _caso_de_uso = std::make_shared<ListarDevolucaoAtrasada::UseCase>(
            _repositorio->getEmprestimos(),
            _repositorio->getLivros(),
            _repositorio->getEditoras(),
            _repositorio->getAutores()
        );

        _tabela = TabelaConsulta();
        Add(_tabela);

        this->_carregarTabela();
    }

    void ao_entrar() override { this->_carregarTabela(); }
};

#endif //APRESENTACAO_TELAS_DEVOLUCOES_ATRASADAS_H
