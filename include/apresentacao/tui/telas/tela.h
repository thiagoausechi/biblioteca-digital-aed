#ifndef APRESENTACAO_TELAS_TELA_BASE_H
#define APRESENTACAO_TELAS_TELA_BASE_H
#include <utility>

#include "aplicacao/tabelas/repositorio.h"
#include "ftxui/component/component_base.hpp"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

using namespace ftxui;

class Renderizador;

class Tela : public ComponentBase {
    const std::string _titulo;
    Element _cabecalho;
    Element _conteudo;

    Element OnRender() final {
        _conteudo = this->Conteudo();

        return vbox({
            _cabecalho | bold,
            separator() | color(Color::GrayDark),
            _conteudo | vscroll_indicator | flex | frame
        });
    }

protected:
    std::shared_ptr<Renderizador> _renderizador;
    std::shared_ptr<Repositorio> _repositorio;

    virtual Element Conteudo() = 0;

public:
    constexpr static auto NOME_CLASSE = "Tela";

    explicit Tela(const std::string &titulo)
        : _titulo(titulo) {
        if (titulo.empty())
            throw PropriedadeVaziaException("Título", NOME_CLASSE);

        // Conteúdo será substituído pela implementação da classe filha
        _conteudo = text("[PLACEHOLDER]");
        _cabecalho = text(" > " + this->getTitulo());
    }

    [[nodiscard]] std::string getTitulo() const { return this->_titulo; }

    /*
     * Utilizado chamado após todas as dependências,
     * como o renderizador e repositório, terem sido
     * devidamente injetadas, garantindo que não sejam
     * nulas.
     *
     * Ideal para iniciar propriedades como Casos de Uso
     * utilizados naquela tela.
     */
    virtual void inicializar() = 0;

    void injetarRenderizador(std::shared_ptr<Renderizador> renderizador) {
        this->_renderizador = renderizador;
    }

    void injetarRepositorio(std::shared_ptr<Repositorio> repositorio) {
        this->_repositorio = repositorio;
    }
};

#endif //APRESENTACAO_TELAS_TELA_BASE_H
