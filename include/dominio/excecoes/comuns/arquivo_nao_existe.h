#ifndef DOMINIO_EXCECOES_COMUNS_ARQUIVO_NAO_EXISTE_H
#define DOMINIO_EXCECOES_COMUNS_ARQUIVO_NAO_EXISTE_H
#include <exception>
#include <format>
#include <string>

class ArquivoNaoExisteException final : public std::exception {
    int _id_arquivo;
    std::string _nome_arquivo;

public:
    explicit ArquivoNaoExisteException(int id_arquivo, const std::string &nome_arquivo)
        : _id_arquivo(id_arquivo),
          _nome_arquivo(nome_arquivo) {
    }

    [[nodiscard]] const char *what() const noexcept override {
        return std::format("Registro de ID '{}' de {} não encontrado", _id_arquivo, _nome_arquivo).c_str();
    }
};

#endif //DOMINIO_EXCECOES_COMUNS_ARQUIVO_NAO_EXISTE_H
