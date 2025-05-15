#ifndef TELA_H
#define TELA_H
#include "ftxui/component/component_base.hpp"

class abstract Tela {
public:
    virtual ~Tela() = default;

    virtual ftxui::Component *renderizar() = 0;
};

#endif //TELA_H
