#include <iostream>
#include <clocale>

#include "utils/menu.h"

using namespace std;

// TODO: Limpar código temporário
inline void NAO_IMPLEMENTADO() {
    std::cout << RED << "Não implementado!" << RESET << std::endl;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    const Menu menu;
    menu.exibir();

    return 0;
}
