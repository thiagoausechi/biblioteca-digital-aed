#ifndef OPCAO_MENU_H
#define OPCAO_MENU_H
#include <ftxui/component/component_base.hpp>

#include "apresentacao/tui/telas/tela.h"
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
    auto selecionado = estado.active;
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

    if (!selecionado)
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
    bool _selecionado = false;
    bool _hovered = false;

    std::shared_ptr<Tela> _tela;

    // Necessário para o reflect, do FTXUI, funcionar corretamente
    Box _box;

    Element OnRender() override {
        const bool esta_focado = Focused();

        const EntryState state{
            /*
             * Descrição passada como argumento para o construtor
             * e já atribuida na classe base `MenuEntryOption`.
             */
            label(),

            /*
             * Indica quando o Mouse está em cima do elemento.
             * Isso é diferente de `_selecionado` e `esta_focado`.
             */
            _hovered, //.state

            /*
             * É, de fato, a atual opção selecionada no Menu.
             */
            _selecionado, //.active

            /*
             * Usado como indicador de navegação. Ao pressionar Enter
             * esta opção será a selecionada.
             */
            esta_focado, //.focused

            /*
             * Índice da opção no menu. Ele é influenciado
             * por outros componentes que estão na mesma lista
             * de "filhos" mesmo eles não sendo do tipo Opção.
             *
             * Exemplo:
             * Opção -> Index(0)
             * Categoria
             * Opção -> Index(2)
             */
            Index()
        };

        Element elemento = (transform ? transform : TransformacaoPadrao)(state);

        if (esta_focado)
            elemento |= focus;

        return elemento | reflect(_box);
    }

    [[nodiscard]] bool Focusable() const override { return true; }

    bool OnEvent(Event evento) override {
        if (evento.is_mouse()) return _tratarEventoDoMouse(evento);
        return false;
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

public:
    constexpr static auto NOME_CLASSE = "Opção do Menu";

    OpcaoComponent(const std::string &descricao, std::shared_ptr<Tela> tela)
        : MenuEntryOption({.label = descricao}) {
        if (descricao.empty())
            throw PropriedadeVaziaException("Descrição", NOME_CLASSE);
        if (tela == nullptr)
            throw PropriedadeVaziaException("Tela", NOME_CLASSE);

        this->_tela = std::move(tela);
    }

    [[nodiscard]] auto getTela() const { return this->_tela; }

    void selecionar() { this->_selecionado = true; }
    void desselecionar() { this->_selecionado = false; }
};

inline auto Opcao(const std::string &descricao, std::shared_ptr<Tela> tela) {
    return Make<OpcaoComponent>(descricao, std::move(tela));
}

#endif //OPCAO_MENU_H
