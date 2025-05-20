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

    int DEBUG_click_count = 0;

    Element Conteudo() override {
        Component input_descricao;
        Component botao_inserir;
        Component formulario;
        Component layout;

        input_descricao
                = Input(
                      &this->_dados_formulario.descricao,
                      "Descrição/nome do Gênero"
                  ) | CatchEvent([&](const Event &evento) {
                      return !evento.is_mouse() && evento == Event::Return;
                  });

        botao_inserir = Button("Contagem: " + std::to_string(DEBUG_click_count), [&] {
            DEBUG_click_count++;
        });

        formulario = Container::Vertical({
            input_descricao,
            botao_inserir
        });

        layout = Renderer(formulario, [&] {
            return vbox({
                hbox(text("Descrição: "), input_descricao->Render()),
                botao_inserir->Render()
            });
        });
        this->Add(layout);

        return layout->Render();
    }

public:
    explicit TelaInserirGenero()
        : Tela("Formulário para inserção de Gênero") {
    }
};

#endif //TELA_INSERIR_GENERO_H
