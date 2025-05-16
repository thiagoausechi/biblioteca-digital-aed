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
    auto hovered = estado.state;
    auto habilitado = estado.active;
    auto em_foco = estado.focused;

    auto prefixo = text(em_foco ? "[" : " ");
    auto sufixo = text(em_foco ? "]" : "");
    auto descricao = text(estado.label);

    if (em_foco) {
        prefixo |= bold | color(Color::YellowLight);
        sufixo |= bold | color(Color::YellowLight);
    }

    auto elemento = hbox({
        prefixo,
        descricao,
        sufixo,
    });

    if (!habilitado)
        elemento |= dim;
    else if (hovered)
        elemento |= inverted;

    return elemento;
}

/*
 * Este componente foi inspirado na classe `MenuEntry` da biblioteca FTXUI.
 * A implementação segue uma lógica semelhante à utilizada no projeto original.
 *
 * Referência:
 * https://github.com/ArthurSonzogni/FTXUI/blob/08b8a3b28f2663f66fca7bb4eea0783d12f76d1d/src/ftxui/component/menu.cpp#L614
 */
class OpcaoComponent final : public ComponentBase, public MenuEntryOption {
    bool _habilitado = true;
    bool _hovered = false;

    std::string _descricao;
    std::function<void()> _acao; // TODO: Refatorar para usar Controller (?) para a ação

    // Necessário para o reflect, do FTXUI, funcionar corretamente
    Box _box;

    Element OnRender() override {
        const bool esta_focado = Focused();

        const EntryState state{
            label(), _hovered, _habilitado, esta_focado, Index()
        };

        Element elemento = (transform ? transform : TransformacaoPadrao)(state);

        if (esta_focado)
            elemento |= focus;

        return elemento | reflect(_box);
    }

    [[nodiscard]] bool Focusable() const override { return this->_habilitado; }

    bool OnEvent(Event evento) override {
        if (evento.is_mouse()) return _tratarEventoDoMouse(evento);
        return _tratarEventoDoTeclado(evento);
    }

    bool _tratarEventoDoMouse(Event evento) {
        this->_hovered = _box.Contain(evento.mouse().x, evento.mouse().y);

        if (!this->_hovered) return false;

        if (evento.mouse().button == Mouse::Left &&
            evento.mouse().motion == Mouse::Pressed) {
            TakeFocus();
            return true;
        }

        return false;
    }

    bool _tratarEventoDoTeclado(Event evento) {
        if (!_habilitado) return false;
        if (!Focused()) return false;

        // Usuário pressionou a tecla de espaço ou enter
        if (evento == Event::Return ||
            evento == Event::Character((" "))) {
            this->_acao();
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

    void habilitar() { this->_habilitado = true; }
    void desabilitar() { this->_habilitado = false; }
    void alternar_habilitado() { this->_habilitado = !this->_habilitado; }
    void alternar_habilitado(const bool forcar_valor) { this->_habilitado = forcar_valor; }
};

inline auto Opcao(const std::string &descricao, std::function<void()> acao) {
    return Make<OpcaoComponent>(descricao, std::move(acao));
}

#endif //OPCAO_MENU_H
