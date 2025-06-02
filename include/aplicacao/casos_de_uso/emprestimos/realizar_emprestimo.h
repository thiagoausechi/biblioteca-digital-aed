#ifndef UC_REALIZAR_EMPRESTIMO_H
#define UC_REALIZAR_EMPRESTIMO_H
#include <memory>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/autor.h"
#include "dominio/arquivos/cidade.h"
#include "dominio/arquivos/editora.h"
#include "dominio/arquivos/emprestimo.h"
#include "dominio/arquivos/livro.h"
#include "dominio/arquivos/pessoa.h"
#include "dominio/excecoes/comuns/arquivo_nao_existe.h"
#include "dominio/excecoes/livro/indisponivel.h"

namespace RealizarEmprestimo {
    struct Pedido {
        int id_pessoa;
        int id_livro;
    };

    struct Resposta {
        int id_emprestimo;
    };

    // Requisito 4
    class UseCase final : public CasoDeUso<const Resposta, const Pedido> {
        std::shared_ptr<Tabela<Pessoa>> _pessoas{};
        std::shared_ptr<Tabela<Cidade>> _cidades{};
        std::shared_ptr<Tabela<Livro>> _livros{};
        std::shared_ptr<Tabela<Editora>> _editoras{};
        std::shared_ptr<Tabela<Autor>> _autores{};
        std::shared_ptr<Tabela<Emprestimo>> _emprestimos{};

    public:
        explicit UseCase(
            std::shared_ptr<Tabela<Pessoa>> pessoas,
            std::shared_ptr<Tabela<Cidade>> cidades,
            std::shared_ptr<Tabela<Livro>> livros,
            std::shared_ptr<Tabela<Editora>> editoras,
            std::shared_ptr<Tabela<Autor>> autores,
            std::shared_ptr<Tabela<Emprestimo>> emprestimos)
            : _pessoas(std::move(pessoas))
              , _cidades(std::move(cidades))
              , _livros(std::move(livros))
              , _editoras(std::move(editoras))
              , _autores(std::move(autores))
              , _emprestimos(std::move(emprestimos)) {}

        const Resposta executar(const Pedido pedido) override {
            auto livro = this->_livros->buscar(pedido.id_livro);

            // Requisito 4.2
            if (!this->_pessoas->buscar(pedido.id_pessoa).has_value())
                throw ArquivoNaoExisteException(pedido.id_pessoa, Pessoa::NOME_CLASSE);

            // Requisito 4.3
            if (!livro.has_value())
                throw ArquivoNaoExisteException(pedido.id_livro, Livro::NOME_CLASSE);

            // Requisito 4.6
            if (livro.value()->estaEmprestado())
                throw LivroIndisponivelException(pedido.id_livro);

            // Requisito 4.5
            auto emprestimo = std::make_shared<Emprestimo>();
            emprestimo->setIdPessoa(pedido.id_pessoa);
            emprestimo->setIdLivro(pedido.id_livro);

            // Requisito 4.5.1.3
            livro.value()->emprestar();

            this->_emprestimos->inserir(emprestimo);
            this->_livros->atualizar(livro.value());

            const Resposta resposta{.id_emprestimo = emprestimo->getId()};
            return resposta;
        }
    };
}

#endif //UC_REALIZAR_EMPRESTIMO_H
