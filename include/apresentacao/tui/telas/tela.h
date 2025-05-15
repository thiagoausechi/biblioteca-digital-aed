#ifndef TELA_H
#define TELA_H
#include "ftxui/component/component_base.hpp"

using namespace ftxui;

class Renderizador;

class Tela {
    Renderizador *_renderizador;

public:
    Tela(): _renderizador(nullptr) { ; }
    explicit Tela(Renderizador *renderizador): _renderizador(renderizador) { ; }

    void setRenderizador(Renderizador *renderizador) {
        this->_renderizador = renderizador;
    }

    virtual ~Tela() = default;

    virtual Component getComponent() = 0;
};

#endif //TELA_H
