#ifndef UC_CIDADE_INSERIR_H
#define UC_CIDADE_INSERIR_H
#include <memory>
#include <string>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/cidade.h"

struct Pedido {
    std::string nome;
    std::string uf;
};

class InserirCidadeUC final : public CasoDeUso<void, const Pedido> {
    std::shared_ptr<Tabela<Cidade> > _cidades{};

public:
    explicit InserirCidadeUC(std::shared_ptr<Tabela<Cidade> > repositorio_cidades)
        : _cidades(std::move(repositorio_cidades)) {
    }

    void executar(const Pedido pedido) override {
        auto nova_cidade = std::make_shared<Cidade>();
        nova_cidade->setNome(pedido.nome);
        nova_cidade->setUF(pedido.uf);

        this->_cidades->inserir(nova_cidade);
    }
};


#endif // UC_CIDADE_INSERIR_H
