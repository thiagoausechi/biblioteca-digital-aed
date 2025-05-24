#ifndef APLICACAO_UC_GENEROS_INSERIR_H
#define APLICACAO_UC_GENEROS_INSERIR_H
#include <string>

#include "dominio/arquivos/genero.h"
#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"

namespace InserirGenero {
    struct Pedido {
        std::string descricao;
    };

    class UseCase final : public CasoDeUso<void, const Pedido> {
        std::shared_ptr<Tabela<Genero>> _generos{};

    public:
        explicit UseCase(std::shared_ptr<Tabela<Genero>> repositorio_generos)
            : _generos(std::move(repositorio_generos)) {
        }

        void executar(const Pedido pedido) override {
            auto novo_genero = std::make_shared<Genero>();
            novo_genero->setDescricao(pedido.descricao);

            this->_generos->inserir(novo_genero);
        }
    };
}

#endif //APLICACAO_UC_GENEROS_INSERIR_H
