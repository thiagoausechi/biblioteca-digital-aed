#ifndef DOMINIO_EXCECOES_COMUNS_ID_NEGATIVO_H
#define DOMINIO_EXCECOES_COMUNS_ID_NEGATIVO_H
#include <exception>
#include <string>

class IdNegativoException final : public std::exception {
    std::string _mensagem;

public:
    explicit IdNegativoException(const std::string &nome_arquivo)
        : _mensagem(std::format("ID de {} não pode ser negativo.", nome_arquivo)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return _mensagem.c_str();
    }
};

#endif //DOMINIO_EXCECOES_COMUNS_ID_NEGATIVO_H
