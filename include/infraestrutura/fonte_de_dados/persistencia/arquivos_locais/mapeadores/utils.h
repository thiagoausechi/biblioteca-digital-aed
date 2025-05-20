#ifndef UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
#define UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
#include <fstream>

class Utils {
    template<typename T>
    static void armazenar_propriedade(std::ofstream &arquivo_local, T valor);
};

// Especializações para armazenar propriedades de diferentes tipos
template<>
inline void Utils::armazenar_propriedade(std::ofstream &arquivo_local, std::string valor) {
    size_t tamanho = valor.size();
    arquivo_local.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
    arquivo_local.write(valor.c_str(), tamanho);
}

template<>
inline void Utils::armazenar_propriedade(std::ofstream &arquivo_local, int valor) {
    arquivo_local.write(reinterpret_cast<const char *>(&valor), sizeof(valor));
}

template<>
inline void Utils::armazenar_propriedade(std::ofstream &arquivo_local, bool valor) {
    arquivo_local.write(reinterpret_cast<const char *>(&valor), sizeof(valor));
}

template<>
inline void Utils::armazenar_propriedade(std::ofstream &arquivo_local, time_t valor) {
    arquivo_local.write(reinterpret_cast<const char *>(&valor), sizeof(valor));
}
#endif //UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
