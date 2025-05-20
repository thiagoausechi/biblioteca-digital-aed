#ifndef UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
#define UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
#include <fstream>

class Utils {
    static void armazenar_string(std::ofstream &arquivo_local, std::string str) {
        size_t tamanho = str.size();
        arquivo_local.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
        arquivo_local.write(str.c_str(), tamanho);
    }

    static void armazenar_int(std::ofstream &arquivo_local, int valor) {
        arquivo_local.write(reinterpret_cast<const char *>(&valor), sizeof(valor));
    }
};

#endif //UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
