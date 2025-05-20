#ifndef REPOSITORIOS_H
#define REPOSITORIOS_H
#include "tabela.h"
#include "dominio/arquivos/autor.h"
#include "dominio/arquivos/cidade.h"
#include "dominio/arquivos/genero.h"

class abstract Repositorio {
public:
    virtual ~Repositorio() = default;

    virtual std::shared_ptr<Tabela<Autor>> getAutores() = 0;

    virtual std::shared_ptr<Tabela<Cidade>> getCidades() = 0;

    virtual std::shared_ptr<Tabela<Genero>> getGeneros() = 0;
};

#endif //REPOSITORIOS_H
