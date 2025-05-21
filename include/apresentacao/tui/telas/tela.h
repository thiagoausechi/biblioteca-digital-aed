#ifndef TELA_H
#define TELA_H
#include <utility>

#include "aplicacao/tabelas/repositorio.h"
#include "ftxui/component/component_base.hpp"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

using namespace ftxui;

class Renderizador;

class Tela : public ComponentBase {
    Element OnRender() final {
        Element cabecalho = text(" > " + this->getTitulo());
        Element conteudo = this->Conteudo();

        return vbox({
            cabecalho | bold,
            separator() | color(Color::GrayDark),
            conteudo | vscroll_indicator | flex | frame
        });
    }

protected:
    const std::string _titulo;
    std::shared_ptr<Renderizador> _renderizador;
    std::shared_ptr<Repositorio> _repositorio;

    virtual Element Conteudo() = 0;

public:
    constexpr static auto NOME_CLASSE = "Tela";

    explicit Tela(const std::string &titulo)
        : _titulo(titulo) {
        if (titulo.empty())
            throw PropriedadeVaziaException("Título", NOME_CLASSE);
    }

    [[nodiscard]] std::string getTitulo() const { return this->_titulo; }

    void injetarRenderizador(std::shared_ptr<Renderizador> renderizador) {
        this->_renderizador = std::move(renderizador);
    }

    void injetarRepositorio(std::shared_ptr<Repositorio> repositorio) {
        this->_repositorio = std::move(repositorio);
    }
};

#endif //TELA_H
