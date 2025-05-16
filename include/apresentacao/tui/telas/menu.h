#ifndef TELA_MENU_H
#define TELA_MENU_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <utility>
#include "tela.h"

using namespace ftxui;

// Requisito 8
class TelaMenu final : public Tela {
    int _ultimo_id_opcao = 0;
    int _item_selecionado = 0;
    Components _menu;

public:
    explicit TelaMenu(Components itens_do_menu)
        : Tela("Início")
          , _menu(std::move(itens_do_menu)) {
    }

    Component getComponent() override {
        auto menu_container = Container::Vertical(this->_menu, &this->_item_selecionado);

        return Renderer(menu_container, [this, menu_container] {
            return vbox({
                menu_container->Render()
                | vscroll_indicator
                | frame
                | size(WIDTH, EQUAL, 100)
                | size(HEIGHT, EQUAL, 50)
            });
        });
    }
};

#endif //TELA_MENU_H
