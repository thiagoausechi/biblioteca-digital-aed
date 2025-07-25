#ifndef APRESENTACAO_TELAS_CONSULTAR_AUTORES_H
#define APRESENTACAO_TELAS_CONSULTAR_AUTORES_H
#include <iomanip>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"
#include "apresentacao/tui/componentes/tabela/tabela.h"
#include "apresentacao/tui/componentes/tabela/celula.h"

using namespace ftxui;

class TelaConsultarAutores final : public Tela {
    std::shared_ptr<TabelaComponent> _tabela;

    Element Conteudo() override {
        return hbox({
            separatorEmpty(),
            _tabela->Render() | flex,
            separatorEmpty(),
        });
    }

    void _carregarTabela() const {
        auto autores = this->_repositorio->getAutores();

        if (autores->vazia()) {
            this->_tabela->definirTabelaVazia(Autor::NOME_CLASSE);
            return;
        }

        std::vector<Elements> linhas;
        std::ostringstream id_formatado;

        // Cabeçalho da Tabela
        linhas.emplace_back(Elements{
            celula(text("ID")),
            celula(text("Nome"))
        });

        // Dados da Tabela
        for (const auto &autor: autores->listarTudo()) {
            id_formatado << std::setfill('0') << std::setw(2) << autor->getId();

            linhas.emplace_back(Elements{
                celula(text(id_formatado.str()) | center),
                celula(autor->getNome())
            });

            id_formatado.str("");
            id_formatado.clear();
        }

        this->_tabela->definirDadosTabela(linhas);

        // Estilização de colunas específicas
        this->_tabela->_tabela_base->SelectColumn(1).Decorate(flex);
    }

public:
    explicit TelaConsultarAutores()
        : Tela("Consulta dos Autores registrados") {}

    void inicializar() override {
        _tabela = TabelaConsulta();
        Add(_tabela);

        this->_carregarTabela();
    }

    void ao_entrar() override { this->_carregarTabela(); }
};

#endif //APRESENTACAO_TELAS_CONSULTAR_AUTORES_H
