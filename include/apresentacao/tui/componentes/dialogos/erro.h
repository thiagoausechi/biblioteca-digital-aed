#ifndef DIALOGO_ERRO_H
#define DIALOGO_ERRO_H
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/componentes/componente_seguro.h"

// TODO: Refatorar coisas comuns entre os diálogos em sua própria classe base
class DialogoDeErroComponent : public ComponentBase {
    std::shared_ptr<EstadoDaAplicacao> _estado_do_app;

    Element OnRender() override {
        auto componente = Container::Vertical({
            Button("Fechar", [&] {
                this->_estado_do_app->mensagem_erro.reset();
                this->_estado_do_app->mostrar_dialog = false;
            })
        });

        componente |= Renderer([&](Element componente_filho) {
            return vbox({
                       text("Erro!") | color(Color::Red),
                       separator() | color(Color::Red),
                       componente_filho
                   })
                   | borderStyled(HEAVY, Color::Red);
        });

        return componente->Render();
    }

public:
    DialogoDeErroComponent(std::shared_ptr<EstadoDaAplicacao> estado_da_aplicacao)
        : _estado_do_app(estado_da_aplicacao) {
    }
};

inline auto DialogoDeErro(std::shared_ptr<EstadoDaAplicacao> estado) {
    return Make<DialogoDeErroComponent>(estado);
}

#endif //DIALOGO_ERRO_H
