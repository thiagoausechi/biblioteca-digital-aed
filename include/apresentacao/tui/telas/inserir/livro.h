#ifndef APRESENTACAO_TELAS_INSERIR_LIVRO_H
#define APRESENTACAO_TELAS_INSERIR_LIVRO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "aplicacao/casos_de_uso/livros/inserir.h"
#include "apresentacao/tui/componentes/dialogos/opcoes.h"
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
    constexpr static auto MSG_SUCESSO = "Livro inserido com sucesso!";

    FormularioInsercaoLivro _dados_formulario;
    std::shared_ptr<InserirLivro::UseCase> _caso_de_uso;

    Component _input_nome;
    Component _input_id_editora;
    Component _input_id_autor;
    Component _input_id_genero;
    Component _botao_inserir;
    Component _formulario;

    std::string _nome_editora;
    std::string _nome_autor;
    std::string _nome_genero;

    Element Conteudo() override {
        return vbox({
            hbox(nome(_dados_formulario.nome), _input_nome->Render()),

            // Campo de entrada para o ID da Editor
            hbox(
                nome(_dados_formulario.id_editora),
                _input_id_editora->Render(),
                text('(' + _nome_editora + ')') | dim
            ),
            text(this->_deve_mostrar_aviso_editora()
                     ? AVISO_SEM_EDITORA
                     : ""
            ) | color(Color::Red),

            // Campo de entrada para o ID do(a) Autor(a)
            hbox(
                nome(_dados_formulario.id_autor),
                _input_id_autor->Render(),
                text('(' + _nome_autor + ')') | dim
            ),
            text(this->_deve_mostrar_aviso_autor()
                     ? AVISO_SEM_AUTOR
                     : ""
            ) | color(Color::Red),

            // Campo de entrada para o ID do gênero
            hbox(
                nome(_dados_formulario.id_genero),
                _input_id_genero->Render(),
                text('(' + _nome_genero + ')') | dim
            ),
            text(this->_deve_mostrar_aviso_genero()
                     ? AVISO_SEM_GENERO
                     : ""
            ) | color(Color::Red),

            // Rodapé da tela
            filler(),
            hbox({
                _botao_inserir->Render() | color(Color::GreenLight),
                filler(),
            })
        });
    }

    bool _deve_mostrar_aviso_editora() { return this->_repositorio->getEditoras()->vazia(); }
    bool _deve_mostrar_aviso_autor() { return this->_repositorio->getAutores()->vazia(); }
    bool _deve_mostrar_aviso_genero() { return this->_repositorio->getGeneros()->vazia(); }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoLivro{};
    }

    void _atualizar_nome_editora() {
        try {
            auto editora =
                    _repositorio
                    ->getEditoras()
                    ->buscar(_dados_formulario.id_editora.valor_numerico());
            if (editora.has_value())
                _nome_editora = editora->get()->getNome();
            else
                _nome_editora = "";
        } catch (...) {
            _nome_editora = "";
        }
    }

    void _atualizar_nome_autor() {
        try {
            auto autor =
                    _repositorio
                    ->getAutores()
                    ->buscar(_dados_formulario.id_autor.valor_numerico());
            if (autor.has_value())
                _nome_autor = autor->get()->getNome();
            else
                _nome_autor = "";
        } catch (...) {
            _nome_autor = "";
        }
    }

    void _atualizar_nome_genero() {
        try {
            auto genero =
                    _repositorio
                    ->getGeneros()
                    ->buscar(_dados_formulario.id_genero.valor_numerico());
            if (genero.has_value())
                _nome_genero = genero->get()->getDescricao();
            else
                _nome_genero = "";
        } catch (...) {
            _nome_genero = "";
        }
    }

    void _executar_InserirLivroUC() {
        try {
            this->_caso_de_uso->executar({
                .nome = _dados_formulario.nome.valor,
                .id_editora = _dados_formulario.id_editora.valor_numerico(),
                .id_autor = _dados_formulario.id_autor.valor_numerico(),
                .id_genero = _dados_formulario.id_genero.valor_numerico(),
            });

            this->_renderizador->mostrarDialogo(
                OpcoesDoDialog::Sucesso(MSG_SUCESSO)
            );

            this->_limpar_formulario();
        } catch (const std::exception &e) {
            this->_renderizador->mostrarDialogo(
                OpcoesDoDialog::Erro(e.what())
            );
        }
    }

public:
    explicit TelaInserirLivro()
        : Tela("Formulário para inserção de Livro") {}

    void inicializar() override {
        _caso_de_uso = std::make_shared<InserirLivro::UseCase>(
            _repositorio->getLivros(),
            _repositorio->getEditoras(),
            _repositorio->getAutores(),
            _repositorio->getGeneros()
        );

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
                    [this] { this->_executar_InserirLivroUC(); },
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
