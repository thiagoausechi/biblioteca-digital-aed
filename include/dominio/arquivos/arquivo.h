#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "dominio/excecoes/comuns/id_negativo.h"

// Classe abstrata para arquivos (não pode ser instanciada)
class abstract Arquivo {
    std::string _nome_arquivo;
    int _id = -1;

public:
    virtual ~Arquivo() = default;

    explicit Arquivo(std::string nome_arquivo)
        : _nome_arquivo(std::move(nome_arquivo)) {
    }

    [[nodiscard]] int getId() const { return this->_id; }

    void setId(const int id) {
        if (id < 0)
            throw IdNegativoException(_nome_arquivo);
        this->_id = id;
    }
};

#endif //ARQUIVO_H
