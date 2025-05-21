#ifndef REPOSITORIOS_H
#define REPOSITORIOS_H
#include "tabela.h"
#include "dominio/arquivos/autor.h"
#include "dominio/arquivos/cidade.h"
#include "dominio/arquivos/genero.h"

/*
 * C++ não tem bem uma maneira nativa de
 * fazer Injeção de Dependência, poderíamos
 * utilizar bibliotecas como o Boost.DI,
 * mas não compensa para o projeto.
 *
 * Nesse cenário, a classe Repositorio
 * é uma interface que define os métodos
 * que devem ser implementados pelas classes
 * na de persistência na camada de Infraestrutura.
 */
class Repositorio {
public:
    virtual ~Repositorio() = default;

    virtual std::shared_ptr<Tabela<Autor>> getAutores() = 0;

    virtual std::shared_ptr<Tabela<Cidade>> getCidades() = 0;

    virtual std::shared_ptr<Tabela<Genero>> getGeneros() = 0;
};

#endif //REPOSITORIOS_H
