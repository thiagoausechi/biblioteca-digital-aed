#ifndef UTILS_MASCARAR_CPF_H
#define UTILS_MASCARAR_CPF_H
#include <string>

#include "dominio/excecoes/pessoa/cpf/tamanho_incorreto.h"

inline std::string mascararCPF(const std::string &cpf) {
    if (cpf.length() != 11)
        throw TamanhoCpfIncorretoException();

    std::string mascarado;
    mascarado += cpf.substr(0, 3) + ".";
    mascarado += cpf.substr(3, 3) + ".";
    mascarado += cpf.substr(6, 3) + "-";
    mascarado += cpf.substr(9, 2);

    return mascarado;
}

#endif //UTILS_MASCARAR_CPF_H
