#ifndef DOMINIO_EXCECOES_PESSOA_CPF_TAMANHO_INCORRETO_H
#define DOMINIO_EXCECOES_PESSOA_CPF_TAMANHO_INCORRETO_H
#include <exception>
#include <string>

class CPFTamanhoIncorreto final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return std::string("O tamanho do CPF está incorreto").c_str();
    }
};

#endif //DOMINIO_EXCECOES_PESSOA_CPF_TAMANHO_INCORRETO_H
