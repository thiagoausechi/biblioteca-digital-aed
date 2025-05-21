#ifndef TAMANHO_INCORRETO_H
#define TAMANHO_INCORRETO_H
#include <exception>
#include <string>

class CPFTamanhoIncorreto final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return ("O tamanho do CPF está incorreto").c_str();
    }
};

#endif //TAMANHO_INCORRETO_H
