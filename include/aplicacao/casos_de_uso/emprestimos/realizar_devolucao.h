#ifndef UC_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
#define UC_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
#include <memory>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/emprestimo.h"
#include "dominio/arquivos/livro.h"
#include "dominio/excecoes/comuns/arquivo_nao_existe.h"

namespace RealizarDevolucao {
    struct Pedido {
        int id_emprestimo;
    };

    // Requisito 5
    class UseCase final : public CasoDeUso<void, const Pedido> {
        std::shared_ptr<Tabela<Emprestimo> > _emprestimos{};
        std::shared_ptr<Tabela<Livro> > _livros{};

    public:
        explicit UseCase(
            std::shared_ptr<Tabela<Emprestimo> > repositorio_emprestimos,
            std::shared_ptr<Tabela<Livro> > repositorio_livros)
            : _emprestimos(std::move(repositorio_emprestimos))
              , _livros(std::move(repositorio_livros)) {
        }

        void executar(const Pedido pedido) override {
            auto emprestimo = this->_emprestimos->buscar(pedido.id_emprestimo);

            if (!emprestimo.has_value())
                throw ArquivoNaoExisteException(pedido.id_emprestimo, Emprestimo::NOME_CLASSE);

            auto emprestimo_encontrado = emprestimo.value();
            auto livro = this->_livros->buscar(emprestimo_encontrado->getIdLivro());

            emprestimo_encontrado->devolver();
            livro.value()->devolver();

            this->_emprestimos->atualizar(emprestimo_encontrado);
            this->_livros->atualizar(livro.value());
        }
    };
}

#endif //UC_EMPRESTIMOS_REALIZAR_DEVOLUCAO_H
