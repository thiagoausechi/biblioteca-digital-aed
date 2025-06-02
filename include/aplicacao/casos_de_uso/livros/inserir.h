#ifndef APLICACAO_UC_LIVROS_INSERIR_H
#define APLICACAO_UC_LIVROS_INSERIR_H
#include <memory>
#include <string>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/autor.h"
#include "dominio/arquivos/editora.h"
#include "dominio/arquivos/genero.h"
#include "dominio/arquivos/livro.h"
#include "dominio/excecoes/comuns/arquivo_nao_existe.h"

namespace InserirLivro {
    struct Pedido {
        std::string nome;
        int id_editora;
        int id_autor;
        int id_genero;
    };

    // Requisito 3
    class UseCase final : public CasoDeUso<void, const Pedido> {
        std::shared_ptr<Tabela<Livro>> _livros{};
        std::shared_ptr<Tabela<Editora>> _editoras{};
        std::shared_ptr<Tabela<Autor>> _autores{};
        std::shared_ptr<Tabela<Genero>> _generos{};

    public:
        explicit UseCase(
            std::shared_ptr<Tabela<Livro>> repositorio_livros,
            std::shared_ptr<Tabela<Editora>> repositorio_editoras,
            std::shared_ptr<Tabela<Autor>> repositorio_autores,
            std::shared_ptr<Tabela<Genero>> repositorio_generos)
            : _livros(std::move(repositorio_livros))
              , _editoras(std::move(repositorio_editoras))
              , _autores(std::move(repositorio_autores))
              , _generos(std::move(repositorio_generos)) {}

        void executar(const Pedido pedido) override {
            // Requisito 3.1
            if (!this->_editoras->buscar(pedido.id_editora).has_value())
                throw ArquivoNaoExisteException(pedido.id_editora, "editora");

            // Requisito 3.2
            if (!this->_autores->buscar(pedido.id_autor).has_value())
                throw ArquivoNaoExisteException(pedido.id_autor, "autor");

            // Requisito 3.3
            if (!this->_generos->buscar(pedido.id_genero).has_value())
                throw ArquivoNaoExisteException(pedido.id_genero, "gênero");

            auto novo_livro = std::make_shared<Livro>();
            novo_livro->setNome(pedido.nome);
            novo_livro->setIdEditora(pedido.id_editora);
            novo_livro->setIdAutor(pedido.id_autor);
            novo_livro->setIdGenero(pedido.id_genero);
            novo_livro->devolver();

            this->_livros->inserir(novo_livro);
        }
    };
}

#endif //APLICACAO_UC_LIVROS_INSERIR_H
