
#ifndef DOMINIO_EXCECOES_EMPRESTIMO_DEVOLUCAO_JA_REALIZADA_H
#define DOMINIO_EXCECOES_EMPRESTIMO_DEVOLUCAO_JA_REALIZADA_H
#include <exception>

class DevolucaoJaRealizadaException final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Não é possível realizar a devolução, pois o empréstimo já foi devolvido.";
    }
};

#endif //DOMINIO_EXCECOES_EMPRESTIMO_DEVOLUCAO_JA_REALIZADA_H
