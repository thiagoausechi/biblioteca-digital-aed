#ifndef LAYOUT_APLICACAO_H
#define LAYOUT_APLICACAO_H
#include <ftxui/component/component.hpp>

#include "utils/app_info.h"

using namespace ftxui;

class Renderizador;

class LayoutAplicacaoComponent final : public ComponentBase {
    std::shared_ptr<Renderizador> _renderizador;

    Element OnRender() override {
        // Componentes principais
        Component cabecalho;
        Component conteudo;
        Component rodape;
        Component app;

        // Auxiliares
        auto tela_atual = this->_renderizador->getTelaAtual();

        // Definição/atribuição dos componentes principais
        cabecalho = Renderer([] {
            return text(NOME_APP)
                   | color(Color::CyanLight)
                   | bold
                   | hcenter;
        });

        this->Add(tela_atual);
        conteudo = tela_atual
                   | hcenter
                   | vcenter;
        this->Add(tela_atual);

        rodape = Renderer([] {
            return text(CREDITOS)
                   | dim
                   | hcenter;
        });

        app = Container::Vertical({
                  cabecalho,
                  Renderer([] { return separator(); }),
                  conteudo | flex,
                  Renderer([] { return separator(); }),
                  rodape
              })
              | border;

        return app->Render();
    }

public:
    explicit LayoutAplicacaoComponent(std::shared_ptr<Renderizador> renderizador)
        : _renderizador(std::move(renderizador)) {
    }
};

inline Component Aplicacao(std::shared_ptr<Renderizador> renderizador) {
    return Make<LayoutAplicacaoComponent>(std::move(renderizador));
}

#endif //LAYOUT_APLICACAO_H
