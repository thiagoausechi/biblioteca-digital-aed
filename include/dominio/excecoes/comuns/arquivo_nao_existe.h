#ifndef DOMINIO_EXCECOES_COMUNS_ARQUIVO_NAO_EXISTE_H
#define DOMINIO_EXCECOES_COMUNS_ARQUIVO_NAO_EXISTE_H
#include <exception>
#include <format>
#include <string>

class ArquivoNaoExisteException final : public std::exception {
    std::string _mensagem;

public:
    explicit ArquivoNaoExisteException(int id_arquivo, const std::string &nome_arquivo)
        : _mensagem(std::format("Registro de ID '{}' de {} não encontrado", id_arquivo, nome_arquivo)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return _mensagem.c_str();
    }
};

#endif //DOMINIO_EXCECOES_COMUNS_ARQUIVO_NAO_EXISTE_H
