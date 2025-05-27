#ifndef APRESENTACAO_TELAS_CONSULTAR_CIDADES_H
#define APRESENTACAO_TELAS_CONSULTAR_CIDADES_H
#include <iomanip>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"
#include "apresentacao/tui/componentes/tabela.h"
#include "apresentacao/tui/componentes/tabela/celula.h"

using namespace ftxui;

class TelaConsultarCidades final : public Tela {
    std::shared_ptr<TabelaComponent> _tabela;

    Element Conteudo() override {
        return hbox({
            separatorEmpty(),
            _tabela->Render() | flex,
            separatorEmpty(),
        });
    }

    void _carregarTabela() const {
        auto cidades = this->_repositorio->getCidades();

        if (cidades->vazia()) {
            this->_tabela->definirTabelaVazia(Cidade::NOME_CLASSE);
            return;
        }

        std::vector<Elements> linhas;
        std::ostringstream id_formatado;

        // Cabeçalho da Tabela
        linhas.emplace_back(Elements{
            celula(text("ID")),
            celula(text("UF")),
            celula(text("Cidade"))
        });

        // Dados da Tabela
        for (const auto &cidade: cidades->listarTudo()) {
            id_formatado << std::setfill('0') << std::setw(2) << cidade->getId();

            linhas.emplace_back(Elements{
                celula(text(id_formatado.str()) | center),
                celula(cidade->getUF()),
                celula(cidade->getNome())
            });

            id_formatado.str("");
            id_formatado.clear();
        }

        this->_tabela->definirDadosTabela(linhas);

        // Estilização de colunas específicas
        this->_tabela->_tabela_base->SelectColumn(2).Decorate(flex);
    }

public:
    explicit TelaConsultarCidades()
        : Tela("Consulta das Cidades registradas") {}

    void inicializar() override {
        _tabela = TabelaConsulta();
        Add(_tabela);

        this->_carregarTabela();
    }

    void ao_entrar() override { this->_carregarTabela(); }
};

#endif //APRESENTACAO_TELAS_CONSULTAR_CIDADES_H
