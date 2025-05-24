#ifndef APLICACAO_TABELAS_TABELA_BASE_H
#define APLICACAO_TABELAS_TABELA_BASE_H
#include <concepts>
#include <vector>

#include "dominio/arquivos/arquivo.h"

template<typename T>
concept TipoDerivadoDeArquivo = std::derived_from<T, Arquivo>;

/*
 * Tabela aqui representa uma ‘interface’
 * para "Repositório" ou "DAO" (Data Access Object)
 *
 * Em um 'CRUD' (Create, Read, Update, Delete) haveria
 * ainda o metodo de remoção. Aqui não se
 * fazem necessários, visto que a remoção
 * dificultaria a implementação devido à
 * relação de dependência entre as tabelas/arquivo,
 * além de não ser um requisito do sistema.
 */
template<TipoDerivadoDeArquivo TArquivo>
class Tabela {
    int _ultimo_id = 0;

protected:
    /**
     * Requisito 4.1
     * _ultimo_id++ representa um auto incremento
     */
    int _gerarId() {
        return _ultimo_id++;
    }

public:
    virtual ~Tabela() = default;

    virtual const std::shared_ptr<TArquivo> inserir(std::shared_ptr<TArquivo> novo_arquivo) = 0;

    virtual const std::shared_ptr<TArquivo> atualizar(std::shared_ptr<TArquivo> arquivo_atualizado) = 0;

    virtual const std::optional<const std::shared_ptr<TArquivo>> buscar(int id_procurado) = 0;

    virtual const std::vector<const std::shared_ptr<TArquivo>> listarTudo() = 0;

    [[nodiscard]] int getUltimoId() const { return this->_ultimo_id; }
};

#endif //APLICACAO_TABELAS_TABELA_BASE_H
