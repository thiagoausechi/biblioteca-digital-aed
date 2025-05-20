#ifndef UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
#define UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
#include <fstream>

class Utils {
    template<typename T>
    static void armazenar_propriedade(std::ofstream &arquivo_local, T valor);

    template<typename T>
    static void carregar_propriedade(std::ifstream &arquivo_local, T &propriedade);
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

// Especializações para carregar propriedades de diferentes tipos
template<>
inline void Utils::carregar_propriedade(std::ifstream &arquivo_local, std::string &propriedade) {
    size_t tamanho_string_lida;
    arquivo_local.read(reinterpret_cast<char *>(&tamanho_string_lida), sizeof(tamanho_string_lida));

    if (arquivo_local.eof()) return;

    std::string string_lida(tamanho_string_lida, '\0');
    arquivo_local.read(&string_lida[0], tamanho_string_lida);
    propriedade = string_lida;
}

template<>
inline void Utils::carregar_propriedade(std::ifstream &arquivo_local, int &propriedade) {
    int valor;
    arquivo_local.read(reinterpret_cast<char *>(&valor), sizeof(valor));
    propriedade = valor;
}

template<>
inline void Utils::carregar_propriedade(std::ifstream &arquivo_local, bool &propriedade) {
    bool valor;
    arquivo_local.read(reinterpret_cast<char *>(&valor), sizeof(valor));
    propriedade = valor;
}

#endif //UTILS_MAPEADORES_ARQUIVOS_LOCAIS_H
