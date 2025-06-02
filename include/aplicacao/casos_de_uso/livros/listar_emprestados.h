#ifndef APLICACAO_UC_LIVROS_LISTAR_EMPRESTADOS_H
#define APLICACAO_UC_LIVROS_LISTAR_EMPRESTADOS_H
#include <vector>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/livro.h"

namespace ListarLivrosEmprestados {
    struct Resposta {
        // Requisito 6.1
        std::vector<std::pair<int, std::string>> livros_emprestados;

        // Requisito 6.2
        int quantidade_emprestados;
        int quantidade_disponiveis;

        Resposta()
            : quantidade_emprestados(0)
              , quantidade_disponiveis(0) {}
    };

    // Requisito 6
    class UseCase final : public CasoDeUso<Resposta> {
        std::shared_ptr<Tabela<Livro>> _livros{};

    public:
        explicit UseCase(std::shared_ptr<Tabela<Livro>> repositorio_livros)
            : _livros(std::move(repositorio_livros)) {}

        Resposta executar() override {
            Resposta resposta;

            for (const auto &livro: _livros->listarTudo()) {
                if (livro->estaEmprestado()) {
                    resposta.quantidade_emprestados++;
                    resposta.livros_emprestados.emplace_back(livro->getId(), livro->getNome());
                } else {
                    resposta.quantidade_disponiveis++;
                }
            }

            return resposta;
        }
    };
}

#endif //APLICACAO_UC_LIVROS_LISTAR_EMPRESTADOS_H
