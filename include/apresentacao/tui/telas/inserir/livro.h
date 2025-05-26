#ifndef APRESENTACAO_TELAS_INSERIR_LIVRO_H
#define APRESENTACAO_TELAS_INSERIR_LIVRO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoLivro {
    Campo nome = {
        .nome = "Nome",
        .placeholder = "Nome do Livro"
    };

    Campo id_editora = {
        .nome = "Editora",
        .placeholder = "Digite o ID da editora",
        .numerico = true
    };

    Campo id_autor = {
        .nome = "Autor(a)",
        .placeholder = "Digite o ID do(a) autor(a)",
        .numerico = true
    };

    Campo id_genero = {
        .nome = "Gênero",
        .placeholder = "Digite o ID do gênero",
        .numerico = true
    };
};

class TelaInserirLivro final : public Tela {
    constexpr static auto AVISO_SEM_EDITORA = "Ao menos uma editora deve ser cadastrada para inserir um livro.";
    constexpr static auto AVISO_SEM_AUTOR = "Ao menos um(a) autor(a) deve ser cadastrado(a) para inserir um livro.";
    constexpr static auto AVISO_SEM_GENERO = "Ao menos um gênero deve ser cadastrado para inserir um livro.";
    constexpr static auto BOTAO_INSERIR = "Inserir livro";

    FormularioInsercaoLivro _dados_formulario;

    Component _input_nome;
    Component _input_id_editora;
    Component _input_id_autor;
    Component _input_id_genero;
    Component _botao_inserir;
    Component _formulario;
    Component _layout;

    std::string _nome_editora;
    std::string _nome_autor;
    std::string _nome_genero;

    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | color(Color::Red);
    }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoLivro{};
    }

    void _atualizar_nome_editora() {
        auto editora =
                _repositorio
                ->getEditoras()
                ->buscar(_dados_formulario.id_editora.valor_numerico());
        if (editora.has_value())
            _nome_editora = editora->get()->getNome();
        else
            _nome_editora = "";
    }

    void _atualizar_nome_autor() {
        auto autor =
                _repositorio
                ->getAutores()
                ->buscar(_dados_formulario.id_autor.valor_numerico());
        if (autor.has_value())
            _nome_autor = autor->get()->getNome();
        else
            _nome_autor = "";
    }

    void _atualizar_nome_genero() {
        auto genero =
                _repositorio
                ->getGeneros()
                ->buscar(_dados_formulario.id_genero.valor_numerico());
        if (genero.has_value())
            _nome_genero = genero->get()->getDescricao();
        else
            _nome_genero = "";
    }

public:
    explicit TelaInserirLivro()
        : Tela("Formulário para inserção de Livro") {}

    void inicializar() override {
        _nome_editora = "";
        _nome_autor = "";
        _nome_genero = "";
        _dados_formulario.id_editora.ao_enviar = [this] { this->_atualizar_nome_editora(); };
        _dados_formulario.id_autor.ao_enviar = [this] { this->_atualizar_nome_autor(); };
        _dados_formulario.id_genero.ao_enviar = [this] { this->_atualizar_nome_genero(); };

        _input_nome = criarInput(_dados_formulario.nome);
        _input_id_editora = criarInput(_dados_formulario.id_editora);
        _input_id_autor = criarInput(_dados_formulario.id_autor);
        _input_id_genero = criarInput(_dados_formulario.id_genero);

        _botao_inserir
                = Button(
                    BOTAO_INSERIR,
                    [] {},
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_nome,
            _input_id_editora,
            _input_id_autor,
            _input_id_genero,
            _botao_inserir
        });

        Add(_formulario);
    }
};

#endif //APRESENTACAO_TELAS_INSERIR_LIVRO_H
