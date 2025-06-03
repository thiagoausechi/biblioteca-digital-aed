#ifndef APRESENTACAO_COMPONENTES_TABELA_H
#define APRESENTACAO_COMPONENTES_TABELA_H
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/table.hpp>

using namespace ftxui;

// Este componente que encapsula uma ftxui::Table
class TabelaComponent final : public ComponentBase {
    Element OnRender() override {
        /*
         * Originalmente a classe Table do ftxui
         * não é tratada como um Componente ou
         * sequer um Element. Portanto, o comportamento
         * ao tentar renderizá-la diretamente não é
         * o esperado. Após ela ser renderizada,
         * o seu conteúdo é perdido.
         *
         * Para não ter necessidade de repetirmos
         * o processo de carregamento dos dados a
         * cada renderização, simplesmente fazemos
         * uma cópia da tabela e renderizamos a
         * cópia no lugar da original.
         */
        auto copia_tabela = *this->_tabela_base;
        return copia_tabela.Render();
    }

public:
    /*
     * A Telas que usam este componente
     * podem modificar a estilização da
     * tabela base, por definimos aqui
     * com acesso público.
     */
    std::shared_ptr<Table> _tabela_base;
    std::string msg_nenhum_registro;

    explicit TabelaComponent()
        : _tabela_base(std::make_shared<Table>()) {}

    void definirTabelaVazia() const {
        /*
         * Não é necessário criar uma nova Tabela
         * utilizando o make_shared, podemos
         * simplesmente alterar o conteúdo do ponteiro.
         */
        *this->_tabela_base = Table(std::vector<Elements>{
            {text(msg_nenhum_registro)}
        });

        // Estilização da Tabela Vazia
        this->_tabela_base->SelectColumn(0).DecorateCells(center);
        this->_tabela_base->SelectColumn(0).DecorateCells(flex);
    }

    void definirTabelaVazia(const std::string &nome_arquivo) {
        this->msg_nenhum_registro = std::format("Nenhum registro encontrado em '{}'.", nome_arquivo);
        this->definirTabelaVazia();
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
