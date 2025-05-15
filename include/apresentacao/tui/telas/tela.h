#ifndef TELA_H
#define TELA_H
#include "ftxui/component/component_base.hpp"

using namespace ftxui;

class Renderizador;

class Tela {
protected:
    std::weak_ptr<Renderizador> _renderizador;

public:
    void setRenderizador(std::weak_ptr<Renderizador> renderizador) {
        this->_renderizador = renderizador;
    }

    virtual ~Tela() = default;

    virtual Component getComponent() = 0;
};

#endif //TELA_H
