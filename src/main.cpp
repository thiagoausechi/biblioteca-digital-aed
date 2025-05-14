#include <iostream>
#include <clocale>

#include "utils/terminal_colors.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Portuguese");

    std::cout << BLUE << "Hello, World!" << std::endl;
    return 0;
}
