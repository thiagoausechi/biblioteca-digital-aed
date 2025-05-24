#ifndef INFRA_PERSISTENCIA_UTILS_TABELA_ARQUIVOS_LOCAIS_H
#define INFRA_PERSISTENCIA_UTILS_TABELA_ARQUIVOS_LOCAIS_H
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

#define DIRETORIO_DADOS "data"

class Utils {
public:
    static fs::path get_diretorio_dados() {
        fs::path dados = fs::current_path() / DIRETORIO_DADOS;
        if (!fs::exists(dados))
            fs::create_directory(dados);

        return dados;
    }

    static void salvar_arquivo_local(std::string nome_arquivo, std::string dados) {
        auto caminho_arquivo_local = get_diretorio_dados() / nome_arquivo;
        std::ofstream arquivo_local(caminho_arquivo_local);

        if (!arquivo_local)
            throw std::runtime_error("Erro ao abrir o arquivo: " + nome_arquivo);

        arquivo_local << dados;
        arquivo_local.close();
    }

    static std::string carregar_arquivo_local(std::string nome_arquivo) {
        auto caminho_arquivo_local = get_diretorio_dados() / nome_arquivo;
        std::ifstream arquivo_local(caminho_arquivo_local);

        if (!arquivo_local.is_open())
            throw std::runtime_error("Erro ao abrir o arquivo: " + nome_arquivo);

        std::string dados((std::istreambuf_iterator(arquivo_local)), std::istreambuf_iterator<char>());
        arquivo_local.close();
        return dados;
    }
};

#endif //INFRA_PERSISTENCIA_UTILS_TABELA_ARQUIVOS_LOCAIS_H
