#ifndef APRESENTACAO_TELAS_INSERIR_EDITORA_H
#define APRESENTACAO_TELAS_INSERIR_EDITORA_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoEditora {
    Campo nome = {
        .nome = "Nome",
        .placeholder = "Nome da Editora"
    };

    Campo id_cidade = {
        .nome = "Cidade",
        .placeholder = "Digite o ID da cidade",
        .numerico = true
    };
};

class TelaInserirEditora final : public Tela {
    constexpr static auto AVISO_SEM_CIDADE = "Ao menos uma cidade deve ser cadastrada para inserir uma editora.";
    constexpr static auto BOTAO_INSERIR = "Inserir editora";
    FormularioInsercaoEditora _dados_formulario;

    Component _input_nome;
    Component _input_id_cidade;
    Component _botao_inserir;
    Component _formulario;
    Component _layout;

    std::string _cidade_formatada;

    Element Conteudo() override {
        return vbox({
            hbox(nome(_dados_formulario.nome), _input_nome->Render()),
            hbox(
                nome(_dados_formulario.id_cidade),
                _input_id_cidade->Render(),
                text('(' + _cidade_formatada + ')') | dim
            ),
            text(this->_deve_mostrar_aviso()
                     ? AVISO_SEM_CIDADE
                     : ""
            ) | color(Color::Red),
            filler(),
            hbox({
                _botao_inserir->Render() | color(Color::GreenLight),
                filler(),
            })
        });
    }

    bool _deve_mostrar_aviso() {
        return this->_repositorio->getCidades()->vazia();
    }

    void _limpar_formulario() {
        _dados_formulario = FormularioInsercaoEditora{};
    }

    void _formatar_cidade() {
        auto cidade =
                _repositorio
                ->getCidades()
                ->buscar(_dados_formulario.id_cidade.valor_numerico());
        if (cidade.has_value())
            _cidade_formatada = cidade->get()->to_string();
        else
            _cidade_formatada = "";
    }

public:
    explicit TelaInserirEditora()
        : Tela("Formulário para inserção de Editora`") {}

    void inicializar() override {
        _cidade_formatada = "";
        _dados_formulario.id_cidade.ao_enviar = [this] { this->_formatar_cidade(); };

        _input_nome = criarInput(_dados_formulario.nome);
        _input_id_cidade = criarInput(_dados_formulario.id_cidade);

        _botao_inserir
                = Button(
                    BOTAO_INSERIR,
                    [] {},
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_nome,
            _input_id_cidade,
            _botao_inserir
        });

        Add(_formulario);
    }
};

#endif //APRESENTACAO_TELAS_INSERIR_EDITORA_H
