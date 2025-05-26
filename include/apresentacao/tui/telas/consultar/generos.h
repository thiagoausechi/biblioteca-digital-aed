#ifndef APRESENTACAO_TELAS_CONSULTAR_GENEROS_H
#define APRESENTACAO_TELAS_CONSULTAR_GENEROS_H
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "apresentacao/tui/lib/formularios/campo_de_entrada.h"
#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class TelaConsultarGeneros final : public Tela {
    Element Conteudo() override {
        return text("Esta tela ainda não foi implementada!")
               | dim
               | vcenter
               | hcenter;
    }

public:
    explicit TelaConsultarGeneros()
        : Tela("Consulta dos Gêneros registrados") {}

    void inicializar() override {}
};

#endif //APRESENTACAO_TELAS_CONSULTAR_GENEROS_H
