#ifndef INFRA_PERSISTENCIA_TABELAS_REPOSITORIO_EM_MEMORIA_H
#define INFRA_PERSISTENCIA_TABELAS_REPOSITORIO_EM_MEMORIA_H
#include "aplicacao/tabelas/repositorio.h"
#include "infraestrutura/fonte_de_dados/persistencia/em_memoria/tabelas/tabela.h"

class RepositorioEmMemoria final : public Repositorio {
    std::shared_ptr<TabelaEmMemoria<Autor>> _autores;
    std::shared_ptr<TabelaEmMemoria<Cidade>> _cidades;
    std::shared_ptr<TabelaEmMemoria<Editora>> _editoras;
    std::shared_ptr<TabelaEmMemoria<Emprestimo>> _emprestimos;
    std::shared_ptr<TabelaEmMemoria<Genero>> _generos;
    std::shared_ptr<TabelaEmMemoria<Livro>> _livros;
    std::shared_ptr<TabelaEmMemoria<Pessoa>> _pessoas;

public:
    explicit RepositorioEmMemoria()
        : _autores(std::make_shared<TabelaEmMemoria<Autor>>())
          , _cidades(std::make_shared<TabelaEmMemoria<Cidade>>())
          , _editoras(std::make_shared<TabelaEmMemoria<Editora>>())
          , _emprestimos(std::make_shared<TabelaEmMemoria<Emprestimo>>())
          , _generos(std::make_shared<TabelaEmMemoria<Genero>>())
          , _livros(std::make_shared<TabelaEmMemoria<Livro>>())
          , _pessoas(std::make_shared<TabelaEmMemoria<Pessoa>>()) {
    }

    std::shared_ptr<Tabela<Autor>> getAutores() override { return _autores; }

    std::shared_ptr<Tabela<Cidade>> getCidades() override { return _cidades; }

    std::shared_ptr<Tabela<Editora>> getEditoras() override { return _editoras; }

    std::shared_ptr<Tabela<Emprestimo>> getEmprestimos() override { return _emprestimos; }

    std::shared_ptr<Tabela<Genero>> getGeneros() override { return _generos; }

    std::shared_ptr<Tabela<Livro>> getLivros() override { return _livros; }

    std::shared_ptr<Tabela<Pessoa>> getPessoas() override { return _pessoas; }
};
#endif //INFRA_PERSISTENCIA_TABELAS_REPOSITORIO_EM_MEMORIA_H
