#ifndef CATEGORIA_MENU_H
#define CATEGORIA_MENU_H
#include <ftxui/component/component_base.hpp>

#include "dominio/excecoes/comuns/propriedade_vazia.h"

using namespace ftxui;

class CategoriaComponent final : public ComponentBase {
    std::string _descricao;

    Element OnRender() override {
        return vbox({
            separatorEmpty(),
            text(this->_descricao) | bold | color(Color::GreenLight),
            separator()
        });
    }

public:
    constexpr static auto NOME_CLASSE = "Opção do Menu";

    explicit CategoriaComponent(const std::string &descricao) {
        if (descricao.empty())
            throw PropriedadeVaziaException("Descrição", NOME_CLASSE);

        this->_descricao = descricao;
    }
};

inline auto Categoria(const std::string &descricao) {
    return Make<CategoriaComponent>(descricao);
}

#endif //CATEGORIA_MENU_H
