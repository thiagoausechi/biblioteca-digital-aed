#ifndef TABELA_H
#define TABELA_H
#include <concepts>

#include "dominio/arquivos/arquivo.h"

template<typename T>
concept TipoDerivadoDeArquivo = std::derived_from<T, Arquivo>;

/*
 * Tabela aqui representa uma ‘interface’
 * para "Repositório" ou "DAO" (Data Access Object)
 *
 * Em um 'CRUD' (Create, Read, Update, Delete) haveriam
 * ainda métodos de atualização e remoção. Aqui não se
 * fazem necessários, visto que a atualização pode ocorrer
 * utilizando o próprio ponteiro do arquivo, enquanto
 * a remoção dificultaria a implementação devido à
 * relação de dependência entre as tabelas/arquivo.
 */
template<TipoDerivadoDeArquivo TArquivo>
class abstract Tabela {
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

  virtual TArquivo *inserir(TArquivo *arquivo) = 0;

  virtual std::optional<TArquivo *> buscar(int id_procurado) = 0;

  [[nodiscard]] int getUltimoId() const { return this->_ultimo_id; }
};

#endif //TABELA_H
