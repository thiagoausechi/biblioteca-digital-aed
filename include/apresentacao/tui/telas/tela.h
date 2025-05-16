#ifndef TELA_H
#define TELA_H
#include "ftxui/component/component_base.hpp"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

using namespace ftxui;

class Renderizador;

class Tela {
protected:
    std::string _titulo{};
    std::weak_ptr<Renderizador> _renderizador;

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


    void setRenderizador(std::weak_ptr<Renderizador> renderizador) {
        this->_renderizador = renderizador;
    }

    virtual ~Tela() = default;

    virtual Component getComponent() = 0;
};

#endif //TELA_H
