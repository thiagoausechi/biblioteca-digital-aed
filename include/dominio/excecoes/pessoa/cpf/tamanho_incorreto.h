#ifndef DOMINIO_EXCECOES_PESSOA_CPF_TAMANHO_INCORRETO_H
#define DOMINIO_EXCECOES_PESSOA_CPF_TAMANHO_INCORRETO_H
#include <exception>
#include <string>

class CPFTamanhoIncorreto final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "O tamanho do CPF está incorreto.";
    }
};

#endif //DOMINIO_EXCECOES_PESSOA_CPF_TAMANHO_INCORRETO_H
