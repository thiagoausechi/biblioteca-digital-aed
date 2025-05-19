#ifndef BREADCRUMB_H
#define BREADCRUMB_H
#include <ftxui/component/component.hpp>
#include <utility>

#include "apresentacao/tui/telas/tela.h"

using namespace ftxui;

class BreadcrumbComponent final : public ComponentBase {
    std::shared_ptr<Renderizador> _renderizador;
    Component _separador;

    /*
     * Uma pilha é uma estrutura de dados LIFO (Last In First Out),
     * ou seja, o último elemento adicionado é o primeiro a ser removido.
     * Portanto, para exibir os elementos na ordem correta,
     * precisamos inverter a ordem dos elementos.
     *
     * Aqui usamos um vetor para armazenar as telas facilitando
     * a iteração para exibir na ordem correta.
     */
    auto _organizar_telas() {
        std::vector<std::shared_ptr<Tela>> telas_organizadas;
        auto pilha_temporaria = this->_renderizador->getPilhaDeTelas();

        /*
         * Primeiro usamos uma cópia da pilha original
         * para passar os elementos da pilha para o vetor.
         */
        while (!pilha_temporaria.empty()) {
            auto tela = pilha_temporaria.top();
            pilha_temporaria.pop();
            telas_organizadas.push_back(tela);
        }

        /*
         * Depois invertemos a ordem dos elementos para
         * que eles sejam exibidos na ordem correta.
         *
         * Isso é necessário porque ao passar os elementos
         * da pilha para o vetor eles foram adicionados na ordem
         * inversa (do topo para o fundo), ficando assim:
         * Tela 3, Tela 2, Tela 1
         *
         * E para exibir na ordem correta precisamos inverter
         * a ordem dos elementos, ficando assim:
         * Tela 1, Tela 2, Tela 3
         */
        std::reverse(telas_organizadas.begin(), telas_organizadas.end());

        return telas_organizadas;
    }

    Element OnRender() override {
        auto telas_organizadas = this->_organizar_telas();
        Elements elementos{text(" > ")};

        for (auto indice = 0; indice < telas_organizadas.size(); ++indice) {
            const auto &tela_atual = telas_organizadas.at(indice);
            auto titulo = text(tela_atual->getTitulo());
            auto eh_ultima_tela = indice == telas_organizadas.size() - 1;

            if (!eh_ultima_tela)
                titulo |= dim;

            elementos.emplace_back(titulo);

            // Adiciona o separador entre os elementos
            if (!eh_ultima_tela) {
                auto eh_penultima_tela = indice == telas_organizadas.size() - 2;
                auto separador = _separador->Render();

                if (!eh_penultima_tela)
                    separador |= dim;

                elementos.emplace_back(separador);
            }
        }

        return hbox(elementos);
    }

public:
    explicit BreadcrumbComponent(std::shared_ptr<Renderizador> renderizador,
                                 Component separador
    ) : _renderizador(std::move(renderizador))
        , _separador(std::move(separador)) {
    }
};

inline Component Breadcrumb(std::shared_ptr<Renderizador> renderizador) {
    auto separador_padrao = Renderer([] { return text(" / "); });

    return Make<BreadcrumbComponent>(std::move(renderizador), separador_padrao);
}

inline Component Breadcrumb(std::shared_ptr<Renderizador> renderizador, Component separador) {
    return Make<BreadcrumbComponent>(std::move(renderizador), std::move(separador));
}

#endif //BREADCRUMB_H
