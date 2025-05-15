#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H

#include <ftxui/component/component.hpp>

using namespace ftxui;

class Tela;

class Renderizador {
    /*
     * Trabalhamos com pilha de telas para podermos
     * armazenar o histórico das telas abertas e
     * navegar entre as elas sem perder o estado.
     */
    std::stack<Tela *> _pilha_telas{};
    Tela *TELA_AVISO_SEM_REGISTRO;

public:
    Renderizador();

    [[nodiscard]] Tela *getTelaAtual() const;

    void navegarPara(Tela *nova_tela);

    void retroceder();

    void renderizar() const;

    ~Renderizador();
};

#endif //RENDERIZADOR_H
