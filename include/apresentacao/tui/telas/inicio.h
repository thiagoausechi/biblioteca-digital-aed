#ifndef APRESENTACAO_TELAS_TELA_INICIAL_H
#define APRESENTACAO_TELAS_TELA_INICIAL_H
#include "tela.h"

/*
Ideia para "Logo" do projeto:
 ____  _ _     _ _       _
|  _ \(_) |   | (_)     | |
| |_) |_| |__ | |_  ___ | |_ ___  ___ __ _
|  _ <| | '_ \| | |/ _ \| __/ _ \/ __/ _` |
| |_) | | |_) | | | (_) | ||  __/ (_| (_| |
|_____|___.__/|_|__\___/ \__\___|\___\__,_|
|  __ \(_)     (_) |      | |
| |  | |_  __ _ _| |_ __ _| |
| |  | | |/ _` | | __/ _` | |
| |__| | | (_| | | || (_| | |
|_____/|_|\__, |_|\__\__,_|_|
           __/ |
          |___/
 */

class TelaInicial final : public Tela {
    Element _dicas_navegacao;
    Element _layout;

    Element Conteudo() override {
        return _layout;
    }

public:
    explicit TelaInicial()
        : Tela("Seja bem-vindo(a)!") {
        _dicas_navegacao = vbox({
            text("💡 Dicas de navegação:") | color(Color::YellowLight),
            text("   - Use as teclas de seta (← ↑ ↓ →) ou o mouse para navegar pelo menu."),
            text("   - Pressione Enter (↵) para selecionar uma opção."),
            text("      Obs: Clicar com o mouse apenas destaca a opção, mas não a abre.") | dim,
            text("   - Para sair do programa, pressione Ctrl + C (Windows) ou ⌃C (MacOS)."),
            text("   - O menu lateral pode ser redimensionado com o mouse.")
        });

        _layout = vbox({
            separatorEmpty(),
            _dicas_navegacao
        });
    }
};

#endif //APRESENTACAO_TELAS_TELA_INICIAL_H
