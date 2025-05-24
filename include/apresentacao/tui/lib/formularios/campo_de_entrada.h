#ifndef APRESENTACAO_LIB_FORMULARIOS_INPUT_H
#define APRESENTACAO_LIB_FORMULARIOS_INPUT_H
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

// Input Field
struct Campo {
    std::string nome;
    //O que é mostrado no campo enquanto "valor" estiver vazio
    std::string placeholder;
    std::string valor;
};

static Component criarInput(Campo &campo) {
    return Input(
               &campo.valor,
               campo.placeholder
           ) | CatchEvent([&](const Event &evento) {
               return !evento.is_mouse() && evento == Event::Return;
           });
}

static Element nome(Campo &campo) {
    return text(campo.nome + ": ");
}

#endif //APRESENTACAO_LIB_FORMULARIOS_INPUT_H
