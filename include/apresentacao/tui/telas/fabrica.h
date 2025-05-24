#ifndef APRESENTACAO_TELAS_FABRICA_H
#define APRESENTACAO_TELAS_FABRICA_H
#include "apresentacao/tui/renderizador.h"
#include "aplicacao/tabelas/repositorio.h"

template<class T>
concept TipoDerivadoDeTela = std::derived_from<T, Tela>;

/*
 * Implementação do "Factory Design Pattern".
 * Instancia uma Tela como um ponteiro compartilhado (`make_shared`)
 * e injeta as dependências necessárias, como o renderizador.
 */
class FabricaDeTelas {
    std::shared_ptr<Renderizador> _renderizador;
    std::shared_ptr<Repositorio> _repositorio;

public:
    explicit FabricaDeTelas(
        std::shared_ptr<Repositorio> repositorio,
        std::shared_ptr<Renderizador> renderizador)
        : _repositorio(std::move(repositorio))
          , _renderizador(std::move(renderizador)) {
    }

    template<class TipoDerivadoDeTela, class... Args>
    std::shared_ptr<TipoDerivadoDeTela> criar(Args &&... args) {
        auto nova_tela = std::make_shared<TipoDerivadoDeTela>(std::forward<Args>(args)...);
        nova_tela->injetarRenderizador(_renderizador);
        nova_tela->injetarRepositorio(_repositorio);
        nova_tela->inicializar();
        return nova_tela;
    }
};

#endif //APRESENTACAO_TELAS_FABRICA_H
