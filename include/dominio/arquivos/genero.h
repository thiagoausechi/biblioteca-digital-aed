#ifndef GENERO_H
#define GENERO_H
#include "arquivo.h"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

class Genero final : public Arquivo {
    std::string _descricao{};

public:
    constexpr static auto NOME = "Gênero";

    Genero(): Arquivo(NOME) { ; }

    Genero(const int id, const std::string &descricao): Arquivo(NOME) {
        this->setId(id);
        this->setDescricao(descricao);
    }

    [[nodiscard]] std::string getDescricao() const { return this->_descricao; }

    void setDescricao(const std::string &descricao) {
        if (descricao.empty())
            throw PropriedadeVaziaException("Descrição", NOME);
        this->_descricao = descricao;
    }
};

#endif //GENERO_H
