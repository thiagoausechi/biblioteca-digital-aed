#ifndef DOMINIO_EXCECOES_COMUNS_EXCEDEU_MAXIMO_H
#define DOMINIO_EXCECOES_COMUNS_EXCEDEU_MAXIMO_H
#include <exception>
#include <string>
#include <utility>

class ExcedeuMaximoException final : public std::exception {
    std::string _mensagem;

public:
    explicit ExcedeuMaximoException(
        const std::string &propriedade,
        const std::string &nome_arquivo,
        const int maximo,
        const std::string &unidade = ""
    ) {
        const auto unidade_formatada = unidade.empty() ? "." : " " + unidade + ".";
        _mensagem = std::format(
            "Propriedade '{}' de '{}' não deve exceder {}{}",
            propriedade,
            nome_arquivo,
            maximo,
            unidade_formatada
        );
    }

    [[nodiscard]] const char *what() const noexcept override {
        return _mensagem.c_str();
    }
};
#endif //DOMINIO_EXCECOES_COMUNS_EXCEDEU_MAXIMO_H
