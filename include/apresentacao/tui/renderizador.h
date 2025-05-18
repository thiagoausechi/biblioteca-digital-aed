#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H
#include <memory>
#include <stack>

#include <ftxui/component/component.hpp>

#include "telas/tela.h"

using namespace ftxui;

class Renderizador : public std::enable_shared_from_this<Renderizador> {
    /*
     * Trabalhamos com pilha de telas para podermos
     * armazenar o histórico das telas abertas e
     * navegar entre as elas sem perder o estado.
     */
    std::stack<std::shared_ptr<Tela>> _pilha_telas{};
    std::shared_ptr<Tela> TELA_AVISO_SEM_REGISTRO;

public:
    Renderizador();

    [[nodiscard]] std::shared_ptr<Tela> getTelaAtual();

    [[nodiscard]] const std::stack<std::shared_ptr<Tela>> &getPilhaDeTelas() const;

    void navegarPara(std::shared_ptr<Tela> nova_tela);

    void retroceder();

    void renderizar();

    ~Renderizador();
};

#endif //RENDERIZADOR_H
