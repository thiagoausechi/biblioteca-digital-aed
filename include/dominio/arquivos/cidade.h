#ifndef DOMINIO_ARQUIVOS_CIDADE_H
#define DOMINIO_ARQUIVOS_CIDADE_H
#include "arquivo.h"
#include "dominio/excecoes/comuns/excedeu_maximo.h"
#include "dominio/excecoes/comuns/propriedade_vazia.h"

class Cidade final : public Arquivo {
    std::string _nome{};
    std::string _uf{};

public:
    constexpr static auto NOME_CLASSE = "Cidade";

    Cidade(): Arquivo(NOME_CLASSE) { ; }

    Cidade(const int id, const std::string &nome, const std::string &uf): Arquivo(NOME_CLASSE) {
        this->setId(id);
        this->setNome(nome);
        this->setUF(uf);
    }

    [[nodiscard]] std::string getNome() const {
        if (this->_nome.empty())
            return "[SEM NOME]";
        return this->_nome;
    }

    void setNome(const std::string &nome) {
        if (nome.empty())
            throw PropriedadeVaziaException("Nome", NOME_CLASSE);

        this->_nome = nome;
    }

    [[nodiscard]] std::string getUF() const {
        if (this->_uf.empty())
            return "[SEM UF]";
        return this->_uf;
    }

    void setUF(const std::string &uf) {
        if (uf.empty())
            throw PropriedadeVaziaException("UF", NOME_CLASSE);
        if (uf.size() > 2)
            throw ExcedeuMaximoException("UF", NOME_CLASSE, 2, "caracteres");

        auto uf_formatado = uf;
        std::ranges::transform(uf, uf_formatado.begin(), toupper);

        this->_uf = uf_formatado;
    }

    [[nodiscard]] std::string to_string() const {
        return std::format(
            "{} / {}",
            this->getNome(),
            this->getUF()
        );
    }
};

#endif //DOMINIO_ARQUIVOS_CIDADE_H
