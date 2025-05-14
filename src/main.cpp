#include <iostream>
#include <clocale>

#include "utils/menu.h"
#include "utils/terminal_colors.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Portuguese");

    const Menu menu;
    menu.exibir();

    return 0;
}
