#ifndef AUTOR_H
#define AUTOR_H
#include "arquivo.h"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

class Autor final : public Arquivo {
    std::string _nome{};

public:
    constexpr static auto NOME_CLASSE = "Autor";

    Autor(): Arquivo(NOME_CLASSE) { ; }

    Autor(const int id, const std::string &nome): Arquivo(NOME_CLASSE) {
        this->setId(id);
        this->setNome(nome);
    }

    [[nodiscard]] std::string getNome() const {
        if (this->_nome.empty())
            return "[SEM NOME]";
        return this->_nome;
    }

    void setNome(const std::string &nome) {
        if (nome.empty())
            throw PropriedadeVaziaException("Nome", NOME_CLASSE);

        this->_nome = nome;
    }
};

#endif //AUTOR_H
