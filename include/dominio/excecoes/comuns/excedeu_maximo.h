#ifndef DOMINIO_EXCECOES_COMUNS_EXCEDEU_MAXIMO_H
#define DOMINIO_EXCECOES_COMUNS_EXCEDEU_MAXIMO_H
#include <exception>
#include <string>
#include <utility>

class ExcedeuMaximoException final : public std::exception {
    std::string _nome_propriedade;
    std::string _nome_arquivo;
    int _qnt_maxima;
    std::string _unidade;

public:
    explicit ExcedeuMaximoException(
        std::string propriedade,
        std::string nome_arquivo,
        const int maximo,
        std::string unidade = ""
    )
        : _nome_propriedade(std::move(propriedade))
          , _nome_arquivo(std::move(nome_arquivo))
          , _qnt_maxima(maximo)
          , _unidade(std::move(unidade)) {
    }

    [[nodiscard]] const char *what() const noexcept override {
        const auto unidade_formatada = _unidade.empty() ? "." : " " + _unidade + ".";
        return ("Propriedade '"
                + _nome_propriedade
                + "' de "
                + _nome_arquivo
                + " não deve exceder "
                + std::to_string(_qnt_maxima)
                + unidade_formatada
        ).c_str();
    }
};
#endif //DOMINIO_EXCECOES_COMUNS_EXCEDEU_MAXIMO_H
