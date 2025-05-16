#ifndef OPCAO_MENU_H
#define OPCAO_MENU_H
#include <ftxui/component/component_base.hpp>

#include "dominio/excecoes/comuns/id_negativo.h"
#include "dominio/excecoes/comuns/propriedade_vazia.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"

using namespace ftxui;

/*
 * Transforma o elemento conforme o estado da Opção.
 */
inline Element TransformacaoPadrao(const EntryState &estado) {
    std::string label = (estado.active ? "> " : "  ") + estado.label;
    Element elemento = text(std::move(label));
    if (estado.focused) {
        elemento = elemento | inverted;
    }
    if (estado.active) {
        elemento = elemento | bold;
    }
    return elemento;
}

/*
 * Este componente é espelhado (é inspirada) na
 * classe `MenuEntry` da biblioteca FTXUI.
 */
class OpcaoComponent final : public ComponentBase, public MenuEntryOption {
    int _id = -1;
    bool _habilitado = true;
    bool _hovered = false;

    std::string _descricao;
    std::function<void()> _acao; // TODO: Refatorar para usar Controller (?) para a ação

    // Necessário para o reflect, do FTXUI, funcionar corretamente
    Box _box;

    Element OnRender() override {
        const bool esta_focado = Focused();

        const EntryState state{
            label(), true, _hovered, esta_focado, Index()
        };

        Element elemento = (transform ? transform : TransformacaoPadrao)
                (state);

        if (esta_focado)
            elemento |= focus;

        return elemento | reflect(_box);
    }

    [[nodiscard]] bool Focusable() const override { return this->_habilitado; }

    bool OnEvent(Event evento) override {
        if (!evento.is_mouse()) return false;

        _hovered = _box.Contain(evento.mouse().x, evento.mouse().y);

        if (!_hovered) return false;

        if (evento.mouse().button == Mouse::Left &&
            evento.mouse().motion == Mouse::Pressed) {
            TakeFocus();
            return true;
        }

        return false;
    }

public:
    constexpr static auto NOME_CLASSE = "Opção do Menu";

    OpcaoComponent(const std::string &descricao, std::function<void()> acao)
        : MenuEntryOption({.label = descricao}) {
        if (descricao.empty())
            throw PropriedadeVaziaException("Descrição", NOME_CLASSE);
        if (acao == nullptr)
            throw PropriedadeVaziaException("Ação", NOME_CLASSE);

        this->_descricao = descricao;
        this->_acao = std::move(acao);
    }

    [[nodiscard]] int getId() const { return this->_id; }

    void setId(const int id) {
        if (id < 0)
            throw IdNegativoException(NOME_CLASSE);
        this->_id = id;
    }
};

inline auto Opcao(const std::string &descricao, std::function<void()> acao) {
    return Make<OpcaoComponent>(descricao, std::move(acao));
}

#endif //OPCAO_MENU_H
