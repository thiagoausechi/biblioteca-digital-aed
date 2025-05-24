#ifndef DOMINIO_EXCECOES_PESSOA_CPF_ERRO_VALIDACAO_H
#define DOMINIO_EXCECOES_PESSOA_CPF_ERRO_VALIDACAO_H
#include <exception>

class CpfInvalidoException final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Padrão de CPF incorreto.";
    }
};
#endif //DOMINIO_EXCECOES_PESSOA_CPF_ERRO_VALIDACAO_H
