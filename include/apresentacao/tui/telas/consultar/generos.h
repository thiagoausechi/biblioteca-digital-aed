#ifndef APRESENTACAO_TELAS_CONSULTAR_GENEROS_H
#define APRESENTACAO_TELAS_CONSULTAR_GENEROS_H
#include <iomanip>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"
#include "apresentacao/tui/componentes/tabela/tabela.h"
#include "apresentacao/tui/componentes/tabela/celula.h"

using namespace ftxui;

class TelaConsultarGeneros final : public Tela {
    std::shared_ptr<TabelaComponent> _tabela;

    Element Conteudo() override {
        return hbox({
            separatorEmpty(),
            _tabela->Render() | flex,
            separatorEmpty(),
        });
    }

    void _carregarTabela() const {
        auto generos = this->_repositorio->getGeneros();

        if (generos->vazia()) {
            this->_tabela->definirTabelaVazia(Genero::NOME_CLASSE);
            return;
        }

        std::vector<Elements> linhas;
        std::ostringstream id_formatado;

        // Cabeçalho da Tabela
        linhas.emplace_back(Elements{
            celula(text("ID")),
            celula(text("Descrição"))
        });

        // Dados da Tabela
        for (const auto &genero: generos->listarTudo()) {
            id_formatado << std::setfill('0') << std::setw(2) << genero->getId();

            linhas.emplace_back(Elements{
                celula(text(id_formatado.str()) | center),
                celula(genero->getDescricao())
            });

            id_formatado.str("");
            id_formatado.clear();
        }

        this->_tabela->definirDadosTabela(linhas);

        // Estilização de colunas específicas
        this->_tabela->_tabela_base->SelectColumn(1).Decorate(flex);
    }

public:
    explicit TelaConsultarGeneros()
        : Tela("Consulta dos Gêneros registrados") {}

    void inicializar() override {
        _tabela = TabelaConsulta();
        Add(_tabela);

        this->_carregarTabela();
    }

    void ao_entrar() override { this->_carregarTabela(); }
};

#endif //APRESENTACAO_TELAS_CONSULTAR_GENEROS_H
