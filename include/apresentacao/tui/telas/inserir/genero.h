#ifndef TELA_INSERIR_GENERO_H
#define TELA_INSERIR_GENERO_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

struct FormularioInsercaoGenero {
    std::string descricao;
};

class TelaInserirGenero final : public Tela {
    FormularioInsercaoGenero _dados_formulario;
    Component _input_descricao;
    Component _botao_inserir;
    Component _formulario;
    Component _layout;

    Element Conteudo() override {
        return vbox({
            hbox(text("Descrição: "), _input_descricao->Render()),
            filler(),
            hbox({
                _botao_inserir->Render() | color(Color::GreenLight),
                filler(),
            })
        });
    }

public:
    explicit TelaInserirGenero()
        : Tela("Formulário para inserção de Gênero") {
        _input_descricao
                = Input(
                      &this->_dados_formulario.descricao,
                      "Descrição/nome do Gênero"
                  ) | CatchEvent([&](const Event &evento) {
                      return !evento.is_mouse() && evento == Event::Return;
                  });

        _botao_inserir
                = Button(
                    "Inserir novo gênero",
                    [&] { ; },
                    ButtonOption::Border()
                );

        _formulario = Container::Vertical({
            _input_descricao,
            _botao_inserir
        });

        Add(_formulario);
    }
};

#endif //TELA_INSERIR_GENERO_H
