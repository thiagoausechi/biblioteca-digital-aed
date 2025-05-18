#ifndef TELA_H
#define TELA_H
#include <utility>

#include "ftxui/component/component_base.hpp"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

using namespace ftxui;

class Renderizador;

class Tela : public ComponentBase {
protected:
    std::string _titulo{};
    std::shared_ptr<Renderizador> _renderizador;

public:
    constexpr static auto NOME_CLASSE = "Tela";

    explicit Tela(const std::string &titulo) {
        this->setTitulo(titulo);
    }

    [[nodiscard]] std::string getTitulo() const { return this->_titulo; }

    void setTitulo(const std::string &titulo) {
        if (titulo.empty())
            throw PropriedadeVaziaException("Título", NOME_CLASSE);
        this->_titulo = titulo;
    }


    void setRenderizador(std::shared_ptr<Renderizador> renderizador) {
        this->_renderizador = std::move(renderizador);
    }
};

#endif //TELA_H
