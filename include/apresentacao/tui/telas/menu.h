#ifndef TELA_MENU_H
#define TELA_MENU_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include "tela.h"
#include "utils/menu.h"

using namespace ftxui;

class TelaMenu final : public Tela {
    std::shared_ptr<menu::Menu> _menu;

public:
    explicit TelaMenu(std::shared_ptr<menu::Menu> &menu) : Tela("Início"), _menu(menu) { ; }

    Component getComponent() override {
        // const auto& options = _menu->getOpcoes();

        return Renderer([] {
            return color(Color::Red, text("Menu"));
        });
    }
};

#endif //TELA_MENU_H
