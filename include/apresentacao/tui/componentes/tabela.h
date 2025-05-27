#ifndef APRESENTACAO_COMPONENTES_TABELA_H
#define APRESENTACAO_COMPONENTES_TABELA_H
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/table.hpp>

using namespace ftxui;

// Este componente que encapsula uma ftxui::Table
class TabelaComponent final : public ComponentBase {
    Element OnRender() override {
        auto copia_tabela = *this->_tabela_base;
        return copia_tabela.Render();
    }

public:
    std::shared_ptr<Table> _tabela_base;

    explicit TabelaComponent() : _tabela_base(std::make_shared<Table>()) {}

    void definirTabelaVazia(const std::string &nome_arquivo) const {
        *this->_tabela_base = Table(std::vector<Elements>{
            {
                text(std::format(
                        "Nenhum registro encontrado em '{}'.",
                        nome_arquivo
                    )
                )
            }
        });

        // Estilização da Tabela Vazia
        this->_tabela_base->SelectColumn(0).DecorateCells(center);
        this->_tabela_base->SelectColumn(0).DecorateCells(flex);
    }

    void definirDadosTabela(const std::vector<Elements> &linhas) const {
        *this->_tabela_base = Table(linhas);

        this->_tabela_base->SelectAll().Border(LIGHT);
        this->_tabela_base->SelectAll().SeparatorVertical(LIGHT);

        // Estilização do Cabeçalho
        this->_tabela_base->SelectRow(0).Border(LIGHT);
        this->_tabela_base->SelectRow(0).DecorateCells(color(Color::Red));

        // Seleciona todas as linhas, exceto a primeira
        auto conteudo = this->_tabela_base->SelectRows(1, -1);
        conteudo.DecorateCellsAlternateRow(color(Color::White));
        conteudo.DecorateCellsAlternateRow(dim);
    }

    [[nodiscard]] bool Focusable() const override { return true; }
};

inline auto TabelaConsulta() {
    return Make<TabelaComponent>();
}

#endif //APRESENTACAO_COMPONENTES_TABELA_H
