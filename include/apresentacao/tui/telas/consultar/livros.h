#ifndef APRESENTACAO_TELAS_CONSULTAR_LIVROS_H
#define APRESENTACAO_TELAS_CONSULTAR_LIVROS_H
#include <iomanip>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"
#include "apresentacao/tui/componentes/tabela.h"
#include "apresentacao/tui/componentes/tabela/celula.h"

using namespace ftxui;

class TelaConsultarLivros final : public Tela {
    std::shared_ptr<TabelaComponent> _tabela;
    bool _ao_menos_um_livro_emprestado{};

    Element Conteudo() override {
        return hbox({
            separatorEmpty(),
            vbox({
                _tabela->Render() | flex,
                text(this->_ao_menos_um_livro_emprestado
                         ? "* Livro indisponível"
                         : ""
                ) | color(Color::Red),
            }) | flex,
            separatorEmpty(),
        });
    }

    void _carregarTabela() {
        auto livros = this->_repositorio->getLivros();

        if (livros->vazia()) {
            this->_tabela->definirTabelaVazia(Livro::NOME_CLASSE);
            return;
        }

        std::vector<Elements> linhas;
        std::ostringstream id_formatado;

        // Cabeçalho da Tabela
        linhas.emplace_back(Elements{
            celula(text("ID")),
            celula(text("Nome")),
            celula(text("Gênero")),
            celula(text("Autor")),
            celula(text("Editora")),
        });

        // Dados da Tabela
        for (const auto &livro: livros->listarTudo()) {
            id_formatado << std::setfill('0') << std::setw(2) << livro->getId();
            auto genero =
                    this->_repositorio
                    ->getGeneros()
                    ->buscar(livro->getIdGenero())
                    .value();
            auto autor =
                    this->_repositorio
                    ->getAutores()
                    ->buscar(livro->getIdAutor())
                    .value();
            auto editora =
                    this->_repositorio
                    ->getEditoras()
                    ->buscar(livro->getIdEditora())
                    .value();

            auto id = celula(text(id_formatado.str()));
            auto nome = celula(livro->getNome());
            auto nome_genero = celula(genero->getDescricao());
            auto nome_autor = celula(autor->getNome());
            auto nome_editora = celula(editora->getNome());

            if (livro->estaEmprestado()) {
                this->_ao_menos_um_livro_emprestado = true;

                id |= color(Color::Red);
                nome |= color(Color::Red);
                nome_genero |= color(Color::Red);
                nome_autor |= color(Color::Red);
                nome_editora |= color(Color::Red);
            }

            linhas.emplace_back(Elements{id, nome, nome_genero, nome_autor, nome_editora});

            id_formatado.str("");
            id_formatado.clear();
        }

        this->_tabela->definirDadosTabela(linhas);

        // Estilização de colunas específicas
        this->_tabela->_tabela_base->SelectColumn(1).Decorate(xflex_grow);
        this->_tabela->_tabela_base->SelectColumns(2, -1).Decorate(xflex);
    }

public:
    explicit TelaConsultarLivros()
        : Tela("Consulta das Livros registradas") {}

    void inicializar() override {
        this->_ao_menos_um_livro_emprestado = false;

        _tabela = TabelaConsulta();
        Add(_tabela);

        this->_carregarTabela();
    }

    void ao_entrar() override { this->_carregarTabela(); }
};

#endif //APRESENTACAO_TELAS_CONSULTAR_LIVROS_H
