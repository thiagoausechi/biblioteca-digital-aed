#ifndef PROPRIEDADE_VAZIA_H
#define PROPRIEDADE_VAZIA_H
#include <exception>
#include <string>

class PropriedadeVaziaException final : public std::exception {
    std::string _nome_propriedade;
    std::string _nome_arquivo;

public:
    explicit PropriedadeVaziaException(std::string propriedade, std::string nome_arquivo)
        : _nome_propriedade(std::move(propriedade))
          , _nome_arquivo(std::move(nome_arquivo)) {
    }

    [[nodiscard]] const char *what() const noexcept override {
        return ("Propriedade '" + _nome_propriedade + "' de " + _nome_arquivo + " não pode ser vazia.").c_str();
    }
};

#endif //PROPRIEDADE_VAZIA_H
