#ifndef UTILS_BUSCA_BINARIA_H
#define UTILS_BUSCA_BINARIA_H
#include <vector>

/*
  * Implementação da busca binária para encontrar o
  * índice de um arquivo.
  *
  * Aqui poderíamos utilizar o `std::lower_bound`,
  * mas para fins de aprendizado e entendimento
  * da lógica, implementamos a busca binária
  * manualmente.
  */
template<typename T>
static int encontrarIndicePorId(std::vector<std::shared_ptr<T>> arquivos_sequenciais, int id_procurado) {
    if (arquivos_sequenciais.empty())
        return -1;

    int inicio = 0;
    int fim = static_cast<int>(arquivos_sequenciais.size()) - 1;

    while (inicio <= fim) {
        const int meio = inicio + (fim - inicio) / 2;
        int idAtual = arquivos_sequenciais[meio]->getId();

        if (idAtual == id_procurado)
            return meio;
        if (idAtual < id_procurado)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

#endif //UTILS_BUSCA_BINARIA_H
