#ifndef REPOSITORIOS_H
#define REPOSITORIOS_H
#include "tabela.h"
#include "dominio/arquivos/autor.h"
#include "dominio/arquivos/cidade.h"
#include "dominio/arquivos/genero.h"

class Repositorio {
public:
    std::shared_ptr<Tabela<Autor>> autores = nullptr;
    std::shared_ptr<Tabela<Cidade>> cidades = nullptr;
    std::shared_ptr<Tabela<Genero>> generos = nullptr;
};

#endif //REPOSITORIOS_H
