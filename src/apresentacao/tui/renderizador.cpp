#include <ftxui/dom/elements.hpp>

#include <ftxui/component/screen_interactive.hpp>
#include "apresentacao/tui/renderizador.h"
#include "apresentacao/tui/telas/tela_reserva.h"

Renderizador::Renderizador(): TELA_AVISO_SEM_REGISTRO(new TelaReserva()) { ; }

Tela *Renderizador::getTelaAtual() const {
    if (_pilha_telas.empty())
        return TELA_AVISO_SEM_REGISTRO;
    return _pilha_telas.top();
}

void Renderizador::retroceder() {
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


void Renderizador::renderizar() const {
    auto engine_de_renderizacao = ScreenInteractive::Fullscreen();

    const auto cabecalho = color(Color::CyanLight, text("Biblioteca Digital") | bold | hcenter);
    const auto tela_atual = Container::Vertical({getTelaAtual()->getComponent()}) | hcenter | vcenter;
    const auto rodape = text("Por Lucas Facina & Thiago Ausechi") | dim | hcenter;

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

void Renderizador::navegarPara(Tela *nova_tela) {
    if (_pilha_telas.top() == nova_tela)
        return;

    _pilha_telas.push(nova_tela);
}

Renderizador::~Renderizador() {
    while (!_pilha_telas.empty()) {
        delete _pilha_telas.top();
        _pilha_telas.pop();
    }
}
