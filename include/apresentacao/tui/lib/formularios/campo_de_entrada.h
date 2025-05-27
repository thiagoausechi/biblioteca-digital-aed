#ifndef APRESENTACAO_LIB_FORMULARIOS_INPUT_H
#define APRESENTACAO_LIB_FORMULARIOS_INPUT_H
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>

using namespace ftxui;

// Input Field
struct Campo {
    std::string nome;
    //O que é mostrado no campo enquanto "valor" estiver vazio
    std::string placeholder;
    std::string valor;

    bool numerico = false;

    std::function<void()> ao_mudar_valor = [] {};
    std::function<void()> ao_enviar = [] {};
    std::function<bool(const Event &evento)> escutar_evento = nullptr;

    [[nodiscard]] int valor_numerico() const {
        if (valor.empty())
            throw std::invalid_argument(std::format("Campo de {} não pode ser vazio.", nome));
        try {
            return std::stoi(valor);
        } catch (...) {
            throw std::invalid_argument(std::format("Campo de {} contém valor inválido.", nome));
        }
    }
};

static Component criarInput(Campo &campo) {
    InputOption opcao;
    opcao.on_change = campo.ao_mudar_valor;
    opcao.on_enter = campo.ao_enviar;
    opcao.placeholder = campo.placeholder;
    opcao.multiline = false;

    return Input(
               &campo.valor,
               opcao
           ) | CatchEvent([campo](const Event &evento) {
               if (campo.numerico &&
                   evento.is_character() &&
                   !std::isdigit(evento.character()[0]))
                   // Impede de digitar letras
                   return true;

               return campo.escutar_evento != nullptr ? campo.escutar_evento(evento) : false;
           });
}

static Element nome(Campo &campo) {
    return text(campo.nome + ": ");
}

#endif //APRESENTACAO_LIB_FORMULARIOS_INPUT_H
