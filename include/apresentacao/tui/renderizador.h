#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H
#include <ftxui/dom/elements.hpp>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

inline Component TELA_AVISO_SEM_REGISTRO = Renderer([] {
    return color(Color::Red, text("Nenhuma tela registrada!"));
});

class Renderizador {
    /*
     * Trabalhamos com pilha de telas para podermos
     * armazenar o histórico das telas abertas e
     * navegar entre as elas sem perder o estado.
     */
    std::stack<Component *> _pilha_telas;

public:
    [[nodiscard]] Component *getTelaAtual() const {
        if (_pilha_telas.empty())
            return &TELA_AVISO_SEM_REGISTRO;
        return _pilha_telas.top();
    }

    void navegarPara(Component *nova_tela) {
        _pilha_telas.push(nova_tela);
    }

    void retroceder() {
        // Já estamos na tela inicial
        if (_pilha_telas.size() == 1)
            return;

        /*
         * Libera a memória da tela atual
         * indicando que as informações contidas
         * nela serão descartadas junto.
         *
         * Esse comportamento poder ser considerado
         * perigoso para algumas telas, talvez seja
         * necessária uma confirmação do usuário antes
         * de liberar a tela atual.
         *
         * TODO: Dialog de confirmação ao retroceder
         */
        delete _pilha_telas.top();
        _pilha_telas.pop();
    }

    void renderizar() const {
        auto engine_de_renderizacao = ScreenInteractive::Fullscreen();

        const auto cabecalho = color(Color::CyanLight, text("Biblioteca Digital") | bold | hcenter);
        const auto tela_atual = Container::Vertical({*getTelaAtual()}) | hcenter | vcenter;
        const auto rodape = text("Por Lucas Facina e Thiago Ausechi") | dim | hcenter;

        const auto layout_da_aplicacao = Renderer(tela_atual, [&] {
            return vbox({
                cabecalho,
                separator(),
                tela_atual->Render() | flex,
                separator(),
                rodape,
            });
        }) | border;

        engine_de_renderizacao.Loop(layout_da_aplicacao);
    }

    ~Renderizador() {
        while (!_pilha_telas.empty()) {
            delete _pilha_telas.top();
            _pilha_telas.pop();
        }
    }
};

#endif //RENDERIZADOR_H
