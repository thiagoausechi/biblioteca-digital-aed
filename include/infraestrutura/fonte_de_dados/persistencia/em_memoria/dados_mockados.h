#ifndef INFRA_PERSISTENCIA_DADOS_MOCKADOS_EM_MEMORIA_H
#define INFRA_PERSISTENCIA_DADOS_MOCKADOS_EM_MEMORIA_H
#include <memory>

#include "aplicacao/casos_de_uso/autores/inserir.h"
#include "aplicacao/casos_de_uso/cidades/inserir.h"
#include "aplicacao/casos_de_uso/editoras/inserir.h"
#include "aplicacao/casos_de_uso/generos/inserir.h"
#include "aplicacao/casos_de_uso/livros/inserir.h"
#include "aplicacao/casos_de_uso/pessoas/inserir.h"
#include "aplicacao/tabelas/repositorio.h"

/*
 * Esta classe é responsável por inserir dados mockados (falsos ou simulados) no repositório,
 * visando facilitar o desenvolvimento, testes e demonstrações da aplicação.
 *
 * Dados mockados são criados para simular o comportamento de dados reais, permitindo que
 * funcionalidades do sistema sejam testadas mesmo na ausência de uma base de dados real ou
 * de integrações completas. Essa prática ajuda a garantir que o sistema funcione conforme
 * esperado em diferentes cenários, de forma rápida e controlada, sem depender de dados externos
 * ou ambientes de produção.
 */
class MockEmMemoria {
    static void inserirCidades(const std::shared_ptr<Repositorio> &repositorio) {
        const auto inserir = std::make_shared<InserirCidade::UseCase>(repositorio->getCidades());

        inserir->executar({"Rio de Janeiro", "RJ"});
        inserir->executar({"São Paulo", "SP"});
        inserir->executar({"Louveira", "SP"});
    }

    static void inserirPessoas(const std::shared_ptr<Repositorio> &repositorio) {
        const auto inserir = std::make_shared<InserirPessoa::UseCase>(
            repositorio->getPessoas(),
            repositorio->getCidades()
        );

        inserir->executar({"João", "123.456.789-09", "Rua Zero", 0});
        inserir->executar({"José", "123.456.789-09", "Rua Um", 1});
        inserir->executar({"Luiz", "123.456.789-09", "Rua Dois", 2});
    }

    static void inserirAutores(const std::shared_ptr<Repositorio> &repositorio) {
        const auto inserir = std::make_shared<InserirAutor::UseCase>(repositorio->getAutores());

        inserir->executar({"Robert C. Martin"});
        inserir->executar({"Erich Gamma"});
        inserir->executar({"Aditya Y. Bhargava"});
        inserir->executar({"Eric Evans"});
        inserir->executar({"Martin Fowler"});
        inserir->executar({"Andrew Hunt"});
    }

    static void inserirGeneros(const std::shared_ptr<Repositorio> &repositorio) {
        const auto inserir = std::make_shared<InserirGenero::UseCase>(repositorio->getGeneros());

        inserir->executar({"Arquitetura de Software"});
        inserir->executar({"Ciência da Computação"});
        inserir->executar({"Boas práticas de programação"});
    }

    static void inserirEditoras(const std::shared_ptr<Repositorio> &repositorio) {
        const auto inserir = std::make_shared<InserirEditora::UseCase>(
            repositorio->getEditoras(),
            repositorio->getCidades()
        );

        inserir->executar({"Pearson", 2});
        inserir->executar({"Novatec", 1});
        inserir->executar({"Alta Books", 0});
    }

    static void inserirLivros(const std::shared_ptr<Repositorio> &repositorio) {
        const auto inserir = std::make_shared<InserirLivro::UseCase>(
            repositorio->getLivros(),
            repositorio->getEditoras(),
            repositorio->getAutores(),
            repositorio->getGeneros()
        );

        inserir->executar({
            "Padrões de Projetos: Soluções Reutilizáveis de Software Orientados a Objetos",
            0, // .editora
            1, // .autor
            0 // .genero
        });
        inserir->executar({
            "Entendendo Algoritmos: Um guia ilustrado para programadores e outros curiosos",
            1, // .editora
            2, // .autor
            1 // .genero
        });
        inserir->executar({
            "Código Limpo: Habilidades Práticas do Agile Software",
            2, // .editora
            0, // .autor
            2 // .genero
        });
        inserir->executar({
            "Arquitetura Limpa: O Guia do Artesão para Estrutura e Design de Software",
            2, // .editora
            0, // .autor
            0 // .genero
        });
        inserir->executar({
            "Domain-Driven Design: Atacando as Complexidades no Coração do Software",
            2, // .editora
            3, // .autor
            0 // .genero
        });
        inserir->executar({
            "Refatoração: Aperfeiçoando o Design de Códigos Existentes",
            1, // .editora
            4, // .autor
            0 // .genero
        });
        inserir->executar({
            "O Programador Pragmático: De Aprendiz a Mestre",
            2, // .editora
            5, // .autor
            2 // .genero
        });
    }

    static void inserirEmprestimoAtrasado(const std::shared_ptr<Repositorio> &repositorio) {
        const auto emprestar = std::make_shared<RealizarEmprestimo::UseCase>(
            repositorio->getPessoas(),
            repositorio->getLivros(),
            repositorio->getEmprestimos()
        );

        emprestar->executar({0, 0});
        emprestar->executar({1, 1});

        // Inserindo um empréstimo atrasado para testes
        auto emprestimo_atrasado =
                repositorio
                ->getEmprestimos()
                ->buscar(0)
                .value();

        // Pré calculo da data
        time_t agora = time(nullptr);
        tm *data_modificada = localtime(&agora);

        data_modificada->tm_mday -= 7; // Atrasado em 1 semana
        emprestimo_atrasado->setDataPrevistaDevolucao(mktime(data_modificada));

        data_modificada->tm_mday -= 14; // Emprestado há 2 semanas
        emprestimo_atrasado->setDataEmprestimo(mktime(data_modificada));

        repositorio->getEmprestimos()->atualizar(emprestimo_atrasado);
    }

public:
    static void inserirDadosMockados(const std::shared_ptr<Repositorio> &repositorio) {
        inserirCidades(repositorio);
        inserirPessoas(repositorio);
        inserirAutores(repositorio);
        inserirGeneros(repositorio);
        inserirEditoras(repositorio);
        inserirLivros(repositorio);
        inserirEmprestimoAtrasado(repositorio);
    }
};

#endif //INFRA_PERSISTENCIA_DADOS_MOCKADOS_EM_MEMORIA_H
