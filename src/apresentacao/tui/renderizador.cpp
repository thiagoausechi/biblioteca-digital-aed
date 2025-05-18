#include <ftxui/dom/elements.hpp>

#include <ftxui/component/screen_interactive.hpp>
#include "apresentacao/tui/renderizador.h"

#include "apresentacao/tui/componentes/layout_aplicacao.h"
#include "apresentacao/tui/telas/tela_reserva.h"

Renderizador::Renderizador(): TELA_AVISO_SEM_REGISTRO(std::make_shared<TelaReserva>()) { ; }

std::shared_ptr<Tela> Renderizador::getTelaAtual() {
    if (_pilha_telas.empty())
        return TELA_AVISO_SEM_REGISTRO;
    return _pilha_telas.top();
}

const std::stack<std::shared_ptr<Tela>> &Renderizador::getPilhaDeTelas() const {
    return this->_pilha_telas;
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
    _pilha_telas.pop();
}

void Renderizador::renderizar() {
    auto engine_de_renderizacao = ScreenInteractive::Fullscreen();
    engine_de_renderizacao.Loop(Aplicacao(shared_from_this()));
}

void Renderizador::navegarPara(std::shared_ptr<Tela> nova_tela) {
    // Evitamos navegar para a mesma tela
    if (!_pilha_telas.empty() && _pilha_telas.top() == nova_tela)
        return;

    nova_tela->setRenderizador(shared_from_this());
    _pilha_telas.push(nova_tela);
}

Renderizador::~Renderizador() {
    while (!_pilha_telas.empty())
        _pilha_telas.pop();
}
