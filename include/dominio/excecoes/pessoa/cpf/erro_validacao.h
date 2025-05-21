#ifndef ERRO_VALIDACAO_H
#define ERRO_VALIDACAO_H
#include <exception>
#include <string>

class CPFErroValidacao final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return ("Padrão de CPF incorreto").c_str();
    }
};
#endif //ERRO_VALIDACAO_H
