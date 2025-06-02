#ifndef APLICACAO_UC_EDITORAS_INSERIR_H
#define APLICACAO_UC_EDITORAS_INSERIR_H
#include <memory>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/editora.h"
#include "dominio/arquivos/cidade.h"
#include "dominio/excecoes/comuns/arquivo_nao_existe.h"

namespace InserirEditora {
    struct Pedido {
        std::string nome;
        int id_cidade;
    };

    class UseCase final : public CasoDeUso<void, const Pedido> {
        std::shared_ptr<Tabela<Editora>> _editoras{};
        std::shared_ptr<Tabela<Cidade>> _cidades{};

    public:
        explicit UseCase(
            std::shared_ptr<Tabela<Editora>> repositorio_editoras,
            std::shared_ptr<Tabela<Cidade>> repositorio_cidades)
            : _editoras(std::move(repositorio_editoras))
              , _cidades(std::move(repositorio_cidades)) {}

        void executar(const Pedido pedido) override {
            if (!this->_cidades->buscar(pedido.id_cidade).has_value())
                throw ArquivoNaoExisteException(pedido.id_cidade, "cidade");

            auto nova_editora = std::make_shared<Editora>();
            nova_editora->setNome(pedido.nome);
            nova_editora->setIdCidade(pedido.id_cidade);

            this->_editoras->inserir(nova_editora);
        }
    };
}

#endif //APLICACAO_UC_EDITORAS_INSERIR_H
