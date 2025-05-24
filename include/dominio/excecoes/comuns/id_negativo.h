#ifndef DOMINIO_EXCECOES_COMUNS_ID_NEGATIVO_H
#define DOMINIO_EXCECOES_COMUNS_ID_NEGATIVO_H
#include <exception>
#include <string>
#include <utility>

class IdNegativoException final : public std::exception {
    std::string _nome_arquivo;

public:
    explicit IdNegativoException(std::string nome_arquivo)
        : _nome_arquivo(std::move(nome_arquivo)) {
    }

    [[nodiscard]] const char *what() const noexcept override {
        return ("ID de " + _nome_arquivo + " não pode ser negativo.").c_str();
    }
};

#endif //DOMINIO_EXCECOES_COMUNS_ID_NEGATIVO_H
