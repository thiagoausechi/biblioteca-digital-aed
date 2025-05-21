#ifndef UC_LISTAR_DEVOLUCAO_ATRASADA_H
#define UC_LISTAR_DEVOLUCAO_ATRASADA_H
#include <string>
#include <vector>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/autor.h"
#include "dominio/arquivos/editora.h"
#include "dominio/arquivos/emprestimo.h"
#include "dominio/arquivos/livro.h"
#include "utils/date.h"

struct Resposta {
    int id_livro;
    std::string nome_livro;
    std::string nome_editora;
    std::string nome_autor;
    std::string data_prevista_devolucao_formatada;
    long dias_atraso;
};

// Requisito 7
class ListarDevolucaoAtrasada final : public CasoDeUso<const std::vector<Resposta>> {
    std::shared_ptr<Tabela<Emprestimo>> _emprestimos{};
    std::shared_ptr<Tabela<Livro>> _livros{};
    std::shared_ptr<Tabela<Editora>> _editoras{};
    std::shared_ptr<Tabela<Autor>> _autores{};

public:
    explicit ListarDevolucaoAtrasada(
        std::shared_ptr<Tabela<Emprestimo>> repositorio_emprestimos,
        std::shared_ptr<Tabela<Livro>> repositorio_livros,
        std::shared_ptr<Tabela<Editora>> repositorio_editoras,
        std::shared_ptr<Tabela<Autor>> repositorio_autores)
        : _emprestimos(repositorio_emprestimos)
          , _livros(repositorio_livros)
          , _editoras(repositorio_editoras)
          , _autores(repositorio_autores) {
    }

    const std::vector<Resposta> executar() override {
        std::vector<Resposta> respostas;
        auto emprestimos = this->_emprestimos->listarTudo();
        time_t agora;
        time(&agora);

        for (const auto &emprestimo: emprestimos) {
            if (emprestimo->estaDevolvido()) continue;
            if (emprestimo->getDataPrevistaDevolucao() > agora) continue;

            auto id_livro = emprestimo->getIdLivro();
            auto livro = this->_livros->buscar(id_livro).value();
            auto nome_livro = livro->getNome();
            auto nome_editora = this->_editoras->buscar(livro->getIdEditora()).value()->getNome();
            auto nome_autor = this->_autores->buscar(livro->getIdAutor()).value()->getNome();
            auto data_prevista_devolucao = formatar_data(emprestimo->getDataPrevistaDevolucao());
            auto dias_atraso = agora - emprestimo->getDataPrevistaDevolucao();

            respostas.emplace_back(Resposta{
                id_livro,
                nome_livro,
                nome_editora,
                nome_autor,
                data_prevista_devolucao,
                dias_atraso
            });
        }

        return respostas;
    }
};

#endif //UC_LISTAR_DEVOLUCAO_ATRASADA_H
