#ifndef UC_LISTAR_EMPRESTADOS_H
#define UC_LISTAR_EMPRESTADOS_H
#include <vector>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/livro.h"

struct Resposta {
    // Requisito 6.1
    std::vector<std::pair<int, std::string>> livros_emprestados;

    // Requisito 6.2
    int quantidade_emprestados;
    int quantidade_disponiveis;
};

// Requisito 6
class ListarLivrosEmprestadosUC final : public CasoDeUso<Resposta> {
    std::shared_ptr<Tabela<Livro>> _livros{};

public:
    explicit ListarLivrosEmprestadosUC(std::shared_ptr<Tabela<Livro>> repositorio_livros)
        : _livros(std::move(repositorio_livros)) {
    }

    Resposta executar() override {
        Resposta resposta = {
            .livros_emprestados{},
            .quantidade_emprestados = 0,
            .quantidade_disponiveis = 0
        };

        for (auto livro: _livros->listarTudo()) {
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

#endif //UC_LISTAR_EMPRESTADOS_H
