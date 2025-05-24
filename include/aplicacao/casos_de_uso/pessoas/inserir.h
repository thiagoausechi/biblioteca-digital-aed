#ifndef APLICACAO_UC_PESSOAS_INSERIR_H
#define APLICACAO_UC_PESSOAS_INSERIR_H
#include <memory>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/pessoa.h"
#include "dominio/arquivos/cidade.h"
#include "dominio/excecoes/comuns/arquivo_nao_existe.h"

namespace InserirPessoa {
    struct Pedido {
        std::string nome;
        std::string cpf;
        std::string endereco;
        int id_cidade;
    };

    // Requisito 2
    class UseCase final : public CasoDeUso<void, const Pedido> {
        std::shared_ptr<Tabela<Pessoa>> _pessoas{};
        std::shared_ptr<Tabela<Cidade>> _cidades{};

    public:
        explicit UseCase(
            std::shared_ptr<Tabela<Pessoa>> repositorio_pessoas,
            std::shared_ptr<Tabela<Cidade>> repositorio_cidades)
            : _pessoas(std::move(repositorio_pessoas))
              , _cidades(std::move(repositorio_cidades)) {
        }

        void executar(const Pedido pedido) override {
            // Requisito 2.2
            if (!this->_cidades->buscar(pedido.id_cidade).has_value())
                throw ArquivoNaoExisteException(pedido.id_cidade, "cidade");

            auto nova_pessoa = std::make_shared<Pessoa>();
            nova_pessoa->setNome(pedido.nome);
            nova_pessoa->setCPF(pedido.cpf);
            nova_pessoa->setEndereco(pedido.endereco);
            nova_pessoa->setIdCidade(pedido.id_cidade);

            this->_pessoas->inserir(nova_pessoa);
        }
    };
}

#endif //APLICACAO_UC_PESSOAS_INSERIR_H
