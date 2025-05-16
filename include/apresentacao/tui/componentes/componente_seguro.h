#ifndef COMPONENTE_SEGURO_H
#define COMPONENTE_SEGURO_H
#include <optional>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

struct EstadoDaAplicacao {
    std::optional<std::string> mensagem_erro;
    bool mostrar_dialog = false;
};

/**
 * @class ComponenteSeguroComponent
 * @brief Este componente encapsula outro componente "perigoso" (que pode lançar exceção) e lida com elas para que o programa não encerre.
 *
* @details Esta classe estende ComponentBase e encapsula um componente filho para fornecer segurança adicional,
 * capturando exceções lançadas durante o tratamento de eventos. Se uma exceção ocorrer, uma mensagem de erro é
 * definida no estado compartilhado da aplicação e exibida apropriadamente.
 */
class ComponenteSeguroComponent : public ComponentBase {
    Component _componente_perigoso;
    std::shared_ptr<EstadoDaAplicacao> _estado_do_app;

public:
    ComponenteSeguroComponent(Component child, std::shared_ptr<EstadoDaAplicacao> estado_da_aplicacao)
        : _componente_perigoso(std::move(child))
          , _estado_do_app(std::move(estado_da_aplicacao)) {
    }

    bool OnEvent(Event event) override {
        try {
            return ComponentBase::OnEvent(event) ||
                   this->_componente_perigoso->OnEvent(event);
        } catch (const std::exception &e) {
            this->_estado_do_app->mensagem_erro = e.what();
            this->_estado_do_app->mostrar_dialog = true;
            return true;
        }
    }

    Element OnRender() override {
        return this->_componente_perigoso->Render();
    }
};

inline Component ComponenteSeguro(Component child, std::shared_ptr<EstadoDaAplicacao> estado) {
    return Make<ComponenteSeguroComponent>(child, estado);
}

#endif //COMPONENTE_SEGURO_H
