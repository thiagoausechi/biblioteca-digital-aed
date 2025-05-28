#ifndef DOMINIO_EXCECOES_LIVRO_INDISPONIVEL_H
#define DOMINIO_EXCECOES_LIVRO_INDISPONIVEL_H
#include <format>
#include <string>

class LivroIndisponivelException final : public std::exception {
    std::string _mensagem;

public:
    explicit LivroIndisponivelException(int id_livro)
        : _mensagem(std::format("Livro com ID {} não está disponível para empréstimo.", id_livro)) {
    }

    [[nodiscard]] const char *what() const noexcept override {
        return this->_mensagem.c_str();
    }
};

#endif //DOMINIO_EXCECOES_LIVRO_INDISPONIVEL_H
