#ifndef DOMINIO_ARQUIVOS_LIVRO_H
#define DOMINIO_ARQUIVOS_LIVRO_H
#include "arquivo.h"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

class Livro final : public Arquivo {
    std::string _nome{};
    int _id_editora{};
    int _id_autor{};
    int _id_genero{};
    bool _emprestado{};

public:
    constexpr static auto NOME_CLASSE = "Livro";

    Livro(): Arquivo(NOME_CLASSE) {}

    Livro(const int id,
          const std::string &nome,
          const int id_editora,
          const int id_autor,
          const int id_genero)
        : Arquivo(NOME_CLASSE) {
        this->setId(id);
        this->setNome(nome);
        this->setIdEditora(id_editora);
        this->setIdAutor(id_autor);
        this->setIdGenero(id_genero);
        this->devolver();
    }

    [[nodiscard]] std::string getNome() const {
        if (this->_nome.empty())
            return "[SEM NOME]";
        return this->_nome;
    }

    void setNome(const std::string &nome) {
        if (nome.empty())
            throw PropriedadeVaziaException("Nome do livro", NOME_CLASSE);

        this->_nome = nome;
    }

    [[nodiscard]] int getIdEditora() const { return this->_id_editora; }

    void setIdEditora(const int id_editora) {
        if (id_editora < 0)
            throw IdNegativoException("editora");

        this->_id_editora = id_editora;
    }

    [[nodiscard]] int getIdAutor() const { return this->_id_autor; }

    void setIdAutor(const int id_autor) {
        if (id_autor < 0)
            throw IdNegativoException("autor");

        this->_id_autor = id_autor;
    }

    [[nodiscard]] int getIdGenero() const { return this->_id_genero; }

    void setIdGenero(const int id_genero) {
        if (id_genero < 0)
            throw IdNegativoException("gênero");

        this->_id_genero = id_genero;
    }

    [[nodiscard]] bool estaEmprestado() const { return this->_emprestado; }

    // Requisito 5.2.1
    void devolver() { this->_emprestado = false; }
    void emprestar() { this->_emprestado = true; }
};

#endif //DOMINIO_ARQUIVOS_LIVRO_H
