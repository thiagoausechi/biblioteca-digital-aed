#ifndef DOMINIO_EXCECOES_COMUNS_PROPRIEDADE_VAZIA_H
#define DOMINIO_EXCECOES_COMUNS_PROPRIEDADE_VAZIA_H
#include <exception>
#include <string>

class PropriedadeVaziaException final : public std::exception {
    std::string _mensagem;

public:
    explicit PropriedadeVaziaException(const std::string &propriedade, const std::string &nome_arquivo)
        : _mensagem(std::format("Propriedade '{}' de '{}' não pode ser vazia.", propriedade, nome_arquivo)) {
    }

    [[nodiscard]] const char *what() const noexcept override {
        return _mensagem.c_str();
    }
};

#endif //DOMINIO_EXCECOES_COMUNS_PROPRIEDADE_VAZIA_H
