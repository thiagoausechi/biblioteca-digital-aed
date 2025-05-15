#ifndef CIDADE_H
#define CIDADE_H
#include "arquivo.h"
#include "dominio/excecoes/comuns/excedeu_maximo.h"
#include "dominio/excecoes/comuns/propriedade_vazia.h"
#include "utils/terminal_colors.h"

class Cidade final : public Arquivo {
    constexpr auto SEM_UF = RED "[SEM UF]" RESET;

    std::string _nome{};
    std::string _uf{};

public:
    constexpr static auto NOME_CLASSE = "Cidade";

    Cidade(): Arquivo(NOME_CLASSE) {
        this->setNome(RED "[SEM NOME]" RESET);
        this->setNome(SEM_UF);
    }

    Cidade(const int id, const std::string &nome, const std::string &uf): Arquivo(NOME_CLASSE) {
        this->setId(id);
        this->setNome(nome);
        this->setUF(uf);
    }

    [[nodiscard]] std::string getNome() const { return this->_nome; }

    void setNome(const std::string &nome) {
        if (nome.empty())
            throw PropriedadeVaziaException("Nome", NOME_CLASSE);

        this->_nome = nome;
    }

    [[nodiscard]] std::string getUF() const { return this->_uf; }

    void setUF(const std::string &uf) {
        if (uf.empty())
            throw PropriedadeVaziaException("UF", NOME_CLASSE);
        if (uf.size() > 2)
            throw ExcedeuMaximoException("UF", NOME_CLASSE, 2, "caracteres");

        if (uf == SEM_UF) {
            this->_uf = uf;
            return;
        }

        auto uf_formatado = uf;
        std::ranges::transform(uf, uf_formatado.begin(), ::toupper);

        this->_uf = uf_formatado;
    }
};

#endif //CIDADE_H
