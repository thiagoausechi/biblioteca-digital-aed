#ifndef APRESENTACAO_TELAS_CONSULTAR_PESSOAS_H
#define APRESENTACAO_TELAS_CONSULTAR_PESSOAS_H
#include <iomanip>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"
#include "apresentacao/tui/componentes/tabela.h"
#include "apresentacao/tui/componentes/tabela/celula.h"
#include "utils/mascarar_cpf.h"

using namespace ftxui;

class TelaConsultarPessoas final : public Tela {
    std::shared_ptr<TabelaComponent> _tabela;

    Element Conteudo() override {
        return hbox({
            separatorEmpty(),
            _tabela->Render() | flex,
            separatorEmpty(),
        });
    }

    void _carregarTabela() const {
        auto pessoas = this->_repositorio->getPessoas();

        if (pessoas->vazia()) {
            this->_tabela->definirTabelaVazia(Pessoa::NOME_CLASSE);
            return;
        }

        std::vector<Elements> linhas;
        std::ostringstream id_formatado;

        // Cabeçalho da Tabela
        linhas.emplace_back(Elements{
            celula(text("ID")),
            celula(text("CPF")),
            celula(text("Nome")),
            celula(text("Endereço")),
            celula(text("Cidade")),
        });

        // Dados da Tabela
        for (const auto &pessoa: pessoas->listarTudo()) {
            id_formatado << std::setfill('0') << std::setw(2) << pessoa->getId();
            auto cidade =
                    this->_repositorio
                    ->getCidades()
                    ->buscar(pessoa->getIdCidade())
                    .value();

            linhas.emplace_back(Elements{
                celula(text(id_formatado.str()) | center),
                celula(mascararCPF(pessoa->getCPF())),
                celula(pessoa->getNome()),
                celula(pessoa->getEndereco()),
                celula(cidade->to_string()),
            });

            id_formatado.str("");
            id_formatado.clear();
        }

        this->_tabela->definirDadosTabela(linhas);

        // Estilização de colunas específicas
        this->_tabela->_tabela_base->SelectColumn(2).Decorate(flex);
        this->_tabela->_tabela_base->SelectColumn(-1).DecorateCells(align_right);
    }

public:
    explicit TelaConsultarPessoas()
        : Tela("Consulta das Pessoas registradas") {}

    void inicializar() override {
        _tabela = TabelaConsulta();
        Add(_tabela);

        this->_carregarTabela();
    }

    void ao_entrar() override { this->_carregarTabela(); }
};

#endif //APRESENTACAO_TELAS_CONSULTAR_PESSOAS_H
