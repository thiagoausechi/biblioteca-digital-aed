#ifndef INFRA_PERSISTENCIA_MAPEADOR_ARQUIVOS_LOCAIS_AUTOR_H
#define INFRA_PERSISTENCIA_MAPEADOR_ARQUIVOS_LOCAIS_AUTOR_H
#include <fstream>
#include <memory>

#include "dominio/arquivos/autor.h"

class MapeadorAutorParaArquivoLocal {
    static void salvar(std::ofstream &arquivo_local, std::shared_ptr<Autor> autor) {
        throw std::runtime_error("Método \"MapeadorDeAutorParaArquivoLocal::paraArquivoLocal\" não implementado");
    }

    static std::shared_ptr<Autor> carregar(std::ifstream &arquivo_local) {
        throw std::runtime_error("Método \"MapeadorDeAutorParaArquivoLocal::deArquivoLocal\" não implementado");
    }
};

#endif //INFRA_PERSISTENCIA_MAPEADOR_ARQUIVOS_LOCAIS_AUTOR_H
