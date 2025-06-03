#ifndef DOMINIO_ARQUIVOS_EMPRESTIMO_H
#define DOMINIO_ARQUIVOS_EMPRESTIMO_H
#include "arquivo.h"

class Emprestimo final : public Arquivo {
    int _id_pessoa{};
    int _id_livro{};
    time_t _data_emprestimo{};
    time_t _data_prevista_devolucao{};
    time_t _data_efetiva_devolucao{};

public:
    constexpr static auto NOME_CLASSE = "Empréstimo";

    Emprestimo(): Arquivo(NOME_CLASSE) {
        // Requisito 4.5.1.1
        time_t agora = time(nullptr);
        this->setDataEmprestimo(agora);

        // Requisito 4.5.1.2
        tm *data_prevista_devolucao = localtime(&agora);
        data_prevista_devolucao->tm_mday += 7;
        this->setDataPrevistaDevolucao(mktime(data_prevista_devolucao));
    }

    Emprestimo(
        const int id,
        const int id_pessoa,
        const int id_livro,
        const time_t data_emprestimo,
        const time_t data_prevista_devolucao,
        const time_t data_efetiva_devolucao
    ) : Arquivo(NOME_CLASSE) {
        this->setId(id);
        this->setIdPessoa(id_pessoa);
        this->setIdLivro(id_livro);
        this->setDataEmprestimo(data_emprestimo);
        this->setDataPrevistaDevolucao(data_prevista_devolucao);
        this->_data_efetiva_devolucao = data_efetiva_devolucao;
    }

    [[nodiscard]] int getIdPessoa() const { return this->_id_pessoa; }

    void setIdPessoa(const int id_pessoa) {
        if (id_pessoa < 0)
            throw IdNegativoException("pessoa");

        this->_id_pessoa = id_pessoa;
    }

    [[nodiscard]] int getIdLivro() const { return this->_id_livro; }

    void setIdLivro(const int id_livro) {
        if (id_livro < 0)
            throw IdNegativoException("livro");

        this->_id_livro = id_livro;
    }

    [[nodiscard]] time_t getDataEmprestimo() const { return this->_data_emprestimo; }

    void setDataEmprestimo(const time_t data_emprestimo) {
        this->_data_emprestimo = data_emprestimo;
    }

    [[nodiscard]] time_t getDataPrevistaDevolucao() const { return this->_data_prevista_devolucao; }

    void setDataPrevistaDevolucao(const time_t data_prevista_devolucao) {
        this->_data_prevista_devolucao = data_prevista_devolucao;
    }

    [[nodiscard]] time_t getDataEfetivaDevolucao() const { return this->_data_efetiva_devolucao; }

    // Requisito 5.2
    [[nodiscard]] bool estaDevolvido() const { return this->_data_efetiva_devolucao != 0; }

    // Requisito 5.2.1
    void devolver() {
        time_t agora = time(nullptr);
        this->_data_efetiva_devolucao = agora;
    }
};

#endif //DOMINIO_ARQUIVOS_EMPRESTIMO_H
