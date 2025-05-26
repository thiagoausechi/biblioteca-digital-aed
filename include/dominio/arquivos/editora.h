#ifndef DOMINIO_ARQUIVOS_EDITORA_H
#define DOMINIO_ARQUIVOS_EDITORA_H
#include "arquivo.h"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

class Editora final : public Arquivo {
    std::string _nome{};
    int _id_cidade{};

public:
    constexpr static auto NOME_CLASSE = "Editora";

    Editora(): Arquivo(NOME_CLASSE) {}

    Editora(const int id, const std::string &nome, const int id_cidade): Arquivo(NOME_CLASSE) {
        this->setId(id);
        this->setNome(nome);
        this->setIdCidade(id_cidade);
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

    [[nodiscard]] int getIdCidade() const { return this->_id_cidade; }

    void setIdCidade(const int id_cidade) {
        if (id_cidade < 0)
            throw IdNegativoException("cidade");

        this->_id_cidade = id_cidade;
    }
};

#endif //DOMINIO_ARQUIVOS_EDITORA_H
