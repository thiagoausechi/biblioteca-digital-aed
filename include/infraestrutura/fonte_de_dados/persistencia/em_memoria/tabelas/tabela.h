#ifndef INFRA_PERSISTENCIA_TABELAS_TABELA_EM_MEMORIA_H
#define INFRA_PERSISTENCIA_TABELAS_TABELA_EM_MEMORIA_H
#include "aplicacao/tabelas/tabela.h"
#include "utils/busca_binaria.h"

/*
 * Implementação concreta de uma tabela em memória.
 * Esta implementação é útil para testes e desenvolvimento,
 * pois não persiste os dados em disco e, portanto,
 * é extremamente rápida, porém volátil.
 *
 * Em produção, deve-se utilizar uma implementação
 * que persista os dados em disco, como um banco de dados
 * relacional ou um banco de dados NoSQL, ou simplesmente
 * um arquivo local de texto/binário.
 */
template<TipoDerivadoDeArquivo TArquivo>
class TabelaEmMemoria final : public Tabela<TArquivo> {
    std::vector<std::shared_ptr<TArquivo>> _arquivos;

public:
    std::shared_ptr<TArquivo> inserir(std::shared_ptr<TArquivo> novo_arquivo) override {
        novo_arquivo->setId(this->_gerarId());
        _arquivos.push_back(novo_arquivo);
        return novo_arquivo;
    }

    std::shared_ptr<TArquivo> atualizar(std::shared_ptr<TArquivo> arquivo_atualizado) override {
        int indice = encontrarIndicePorId(_arquivos, arquivo_atualizado->getId());
        if (indice == -1)
            return nullptr;

        _arquivos[indice] = arquivo_atualizado;
        return arquivo_atualizado;
    }

    std::optional<std::shared_ptr<TArquivo>> buscar(int id_procurado) override {
        int indice = encontrarIndicePorId(_arquivos, id_procurado);
        if (indice == -1)
            return std::nullopt;

        return _arquivos[indice];
    }

    /*
     * É importante fazermos uma cópia para que
     * não caiamos no erro de modificar o vetor
     * original de arquivos diretamente.
     */
    std::vector<std::shared_ptr<TArquivo>> listarTudo() override {
        std::vector<std::shared_ptr<TArquivo>> copia_somente_leitura;
        copia_somente_leitura.reserve(_arquivos.size());

        for (const auto &ptr: _arquivos)
            copia_somente_leitura.push_back(ptr);

        return copia_somente_leitura;
    }

    bool vazia() override {
        return _arquivos.empty();
    }
};

#endif //INFRA_PERSISTENCIA_TABELAS_TABELA_EM_MEMORIA_H
