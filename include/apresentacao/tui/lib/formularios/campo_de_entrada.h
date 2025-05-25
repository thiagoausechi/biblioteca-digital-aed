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

    std::function<void()> ao_mudar_valor = [] {};
    std::function<void()> ao_enviar = [] {};
    std::function<bool(const Event &evento)> escutar_evento =
            [](const Event &) { return false; };
};

static Component criarInput(Campo &campo) {
    InputOption opcao = {
        .multiline = false,
        .placeholder = campo.placeholder,
        .on_change = campo.ao_mudar_valor,
        .on_enter = campo.ao_enviar,
    };

    return Input(
               &campo.valor,
               opcao
           ) | CatchEvent([campo](const Event &e) {
               return campo.escutar_evento(e);
           });
}

static Element nome(Campo &campo) {
    return text(campo.nome + ": ");
}

#endif //APRESENTACAO_LIB_FORMULARIOS_INPUT_H
