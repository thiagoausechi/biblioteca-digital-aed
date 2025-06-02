#ifndef APLICACAO_UC_CIDADES_INSERIR_H
#define APLICACAO_UC_CIDADES_INSERIR_H
#include <memory>
#include <string>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/cidade.h"

namespace InserirCidade {
    struct Pedido {
        std::string nome;
        std::string uf;
    };

    class UseCase final : public CasoDeUso<void, const Pedido> {
        std::shared_ptr<Tabela<Cidade>> _cidades{};

    public:
        explicit UseCase(std::shared_ptr<Tabela<Cidade>> repositorio_cidades)
            : _cidades(std::move(repositorio_cidades)) {}

        void executar(const Pedido pedido) override {
            auto nova_cidade = std::make_shared<Cidade>();
            nova_cidade->setNome(pedido.nome);
            nova_cidade->setUF(pedido.uf);

            this->_cidades->inserir(nova_cidade);
        }
    };
}

#endif // APLICACAO_UC_CIDADES_INSERIR_H
