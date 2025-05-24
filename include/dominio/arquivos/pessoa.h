#ifndef DOMINIO_ARQUIVOS_PESSOA_H
#define DOMINIO_ARQUIVOS_PESSOA_H
#include <vector>

#include "arquivo.h"
#include "dominio/excecoes/comuns/propriedade_vazia.h"
#include "dominio/excecoes/pessoa/cpf/cpf_invalido.h"
#include "dominio/excecoes/pessoa/cpf/tamanho_incorreto.h"

class Pessoa final : public Arquivo {
    std::string _nome{};
    std::string _cpf{};
    std::string _endereco{};
    int _id_cidade{};

public:
    constexpr static auto NOME_CLASSE = "Pessoa";

    Pessoa(): Arquivo(NOME_CLASSE) { ; }

    Pessoa(const int id,
           const std::string &nome,
           const std::string &cpf,
           const std::string &endereco,
           const int id_cidade)
        : Arquivo(NOME_CLASSE) {
        this->setId(id);
        this->setNome(nome);
        this->setCPF(cpf);
        this->setEndereco(endereco);
        this->setIdCidade(id_cidade);
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

    [[nodiscard]] std::string getCPF() const {
        if (this->_cpf.empty())
            return "[SEM CPF]";
        return this->_cpf;
    }

    void setCPF(const std::string &cpf) {
        if (cpf.empty())
            throw PropriedadeVaziaException("CPF", NOME_CLASSE);

        // Limpeza e Separação dos Digitos do CPF
        std::string cpfLimpo;
        std::vector<int> digitos;
        digitos.reserve(11);
        for (const char c: cpf)
            if (isdigit(c)) {
                cpfLimpo += c;
                digitos.emplace_back(c - '0');
            }

        if (cpfLimpo.size() != 11)
            throw TamanhoCpfIncorretoException();

        // Algoritmo de Validação do CPF (https://dicasdeprogramacao.com.br/algoritmo-para-validar-cpf/)
        // Requisito 2.1
        bool ehValido = false;
        bool todosDigitosIguais = true;
        for (int i = 1; i < 11; i++) {
            if (digitos[i] != digitos[0]) {
                todosDigitosIguais = false;
                break;
            }
        }

        if (todosDigitosIguais)
            ehValido = false;
        else {
            int soma1 = 0;
            for (int i = 0; i < 9; i++)
                soma1 += digitos[i] * (10 - i);

            int resto1 = (soma1 * 10) % 11;
            if (resto1 == 10)
                resto1 = 0;

            int soma2 = 0;
            for (int i = 0; i < 10; i++)
                soma2 += digitos[i] * (11 - i);

            int resto2 = (soma2 * 10) % 11;
            if (resto2 == 10)
                resto2 = 0;

            ehValido = resto1 == digitos[9] && resto2 == digitos[10];
        }

        if (!ehValido)
            throw CpfInvalidoException();

        this->_cpf = cpfLimpo;
    }

    [[nodiscard]] std::string getEndereco() const {
        if (this->_endereco.empty())
            return "[SEM ENDEREÇO]";
        return this->_endereco;
    }

    void setEndereco(const std::string &endereco) {
        if (endereco.empty())
            throw PropriedadeVaziaException("Endereço", NOME_CLASSE);

        this->_endereco = endereco;
    }

    [[nodiscard]] int getIdCidade() const { return this->_id_cidade; }

    void setIdCidade(const int id_cidade) {
        if (id_cidade < 0)
            throw IdNegativoException("cidade");

        this->_id_cidade = id_cidade;
    }
};

#endif //DOMINIO_ARQUIVOS_PESSOA_H
