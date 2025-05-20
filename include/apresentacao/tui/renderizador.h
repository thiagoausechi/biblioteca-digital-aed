#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H
#include <memory>
#include <ftxui/component/component.hpp>

#include "componentes/menu/categoria.h"
#include "componentes/menu/opcao.h"
#include "ftxui/component/screen_interactive.hpp"
#include "utils/app_info.h"

using namespace ftxui;

class Renderizador : public std::enable_shared_from_this<Renderizador> {
    Components _itens_menu;

    int _indice_item_menu_selecionado;
    int _indice_mapeado_tela_selecionada;

    /*
     * É necessário separar o que é "Categoria"
     * do que é "Opção" (que representa uma tela),
     * com isso, os indices que representam as
     * opções no menu são diferentes dos indices
     * que representam os indices da tela.
     *
     * A variável _mapa_indices é um mapa que
     * associa o indice da Opção no Menu com
     * o indice da Tela:
     *
     * [Itens no Menu] | [Indice da Tela]
     * 0 - Categoria   |         --
     * 1 - Opção       |         00
     * 2 - Opção       |         01
     * 3 - Categoria   |         --
     * 4 - Opção       |         02
     */
    std::unordered_map<int, int> _mapa_indices_opcoes{};

    /*
     * Esta função atualiza o índice da tela
     * selecionada já utilizando um índice
     * mapeado.
     */
    bool _atualizarIndiceTelaSelecionada() {
        auto indice_mapeado =
                this->_mapa_indices_opcoes
                .find(_indice_item_menu_selecionado)
                ->second; // first = indice_item_menu_selecionado

        // Não precisa atualizar se o índice já estiver selecionado
        if (_indice_mapeado_tela_selecionada != indice_mapeado) {
            _indice_mapeado_tela_selecionada = indice_mapeado;
            return true;
        }

        return false;
    }

public:
    explicit Renderizador(Components itens_do_menu)
        : _itens_menu(std::move(itens_do_menu))
          , _indice_item_menu_selecionado(-1)
          , _indice_mapeado_tela_selecionada(-1) {
        if (_itens_menu.empty())
            throw PropriedadeVaziaException("Itens do menu", "Renderizador");

        int ultimo_indice_opcao = 0;
        for (int i = 0; i < _itens_menu.size(); i++) {
            bool eh_opcao = dynamic_cast<OpcaoComponent *>(_itens_menu.at(i).get()) != nullptr;
            if (eh_opcao) {
                bool primeiro_indice_definido = _indice_item_menu_selecionado != -1;
                if (!primeiro_indice_definido) _indice_item_menu_selecionado = i;

                // Armazena o índice da Opção com o índice da Tela
                _mapa_indices_opcoes.emplace(i, ultimo_indice_opcao++);
            }
        }

        if (_indice_item_menu_selecionado == -1)
            throw std::invalid_argument("É necessário ter pelo menos uma opção selecionável (página registrada).");

        this->_atualizarIndiceTelaSelecionada();
    }

    void renderizar() {
        auto engine_de_renderizacao = ScreenInteractive::Fullscreen();
        int largura_menu = 30;

        Component cabecalho;
        Component rodape;
        Component menu_lateral;
        Components telas;
        Component conteudo;
        Component componentes_interativos;
        Component layout_aplicacao;

        /*
         * Armazenas as telas contidas em cada opção
         * num único vetor, para que o Container::Tab
         * possa utilizar.
         */
        for (auto item_menu: _itens_menu) {
            auto componente_opcao = dynamic_cast<OpcaoComponent *>(item_menu.get());
            if (componente_opcao != nullptr)
                telas.emplace_back(componente_opcao->getTela());
        }

        // Definição/atribuição dos componentes
        cabecalho = Renderer([] {
            return text(NOME_APP)
                   | color(Color::CyanLight)
                   | bold
                   | hcenter;
        });

        rodape = Renderer([] {
            return text(CREDITOS)
                   | dim
                   | hcenter;
        });

        menu_lateral =
                Container::Vertical(this->_itens_menu, &this->_indice_item_menu_selecionado)
                | vscroll_indicator
                | frame
                | CatchEvent([&](Event evento) {
                    if (!evento.is_mouse() &&
                        evento == Event::Return ||
                        evento == Event::Character(' ')) {
                        return this->_atualizarIndiceTelaSelecionada();
                    }

                    return false;
                });

        conteudo = Container::Tab(telas, &_indice_mapeado_tela_selecionada)
                   | vscroll_indicator
                   | flex
                   | frame;

        componentes_interativos = ResizableSplitLeft(menu_lateral, conteudo, &largura_menu);

        layout_aplicacao = Renderer(componentes_interativos, [&] {
            return vbox({
                       cabecalho->Render(),
                       separator(),
                       componentes_interativos->Render() | flex,
                       separator(),
                       rodape->Render()
                   }) | border;
        });

        engine_de_renderizacao.Loop(layout_aplicacao);
    }

    ~Renderizador() = default;
};

#endif //RENDERIZADOR_H
