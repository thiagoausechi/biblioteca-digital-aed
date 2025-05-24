#ifndef APLICACAO_UC_AUTORES_INSERIR_H
#define APLICACAO_UC_AUTORES_INSERIR_H
#include <memory>
#include <string>

#include "aplicacao/casos_de_uso/caso_de_uso.h"
#include "aplicacao/tabelas/tabela.h"
#include "dominio/arquivos/autor.h"

namespace InserirAutor {
    struct Pedido {
        std::string nome;
    };

    class UseCase final : public CasoDeUso<void, const Pedido> {
        std::shared_ptr<Tabela<Autor>> _autores{};

    public:
        explicit UseCase(std::shared_ptr<Tabela<Autor>> repositorio_autores)
            : _autores(std::move(repositorio_autores)) {
        }

        void executar(const Pedido pedido) override {
            auto novo_autor = std::make_shared<Autor>();
            novo_autor->setNome(pedido.nome);

            this->_autores->inserir(novo_autor);
        }
    };
}

#endif // APLICACAO_UC_AUTORES_INSERIR_H
