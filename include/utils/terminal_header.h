#ifndef TERMINAL_HEADER_H
#define TERMINAL_HEADER_H

#include <iostream>
#include <stdexcept>

#include "terminal_colors.h"
#include "utf8_length.h"

#define LARGURA_MAX_CABECALHO 64

inline void append(std::string &source, const int n, const std::string &str_to_append) {
    for (int i = 0; i < n; i++)
        source += str_to_append;
}

inline std::string cabecalho(const std::string &titulo) {
    const auto tamanho_titulo = utf8_length(titulo);
    if (tamanho_titulo > LARGURA_MAX_CABECALHO - 2)
        throw std::invalid_argument("Título muito longo.");

    const int espaco_centralizar_titulo = (LARGURA_MAX_CABECALHO - 2 - tamanho_titulo) / 2;

    std::string saida;
    saida.reserve(LARGURA_MAX_CABECALHO * 3 + titulo.length() + 10);

    // Linha superior
    saida = "╭";
    append(saida, LARGURA_MAX_CABECALHO - 2, "─");
    saida.append("╮\n│");

    // Linha central com título
    saida.append(espaco_centralizar_titulo, ' ');
    saida.append(BLUE).append(titulo).append(RESET);
    saida.append(espaco_centralizar_titulo + (tamanho_titulo % 2), ' ');
    saida.append("│\n╰");

    // Linha inferior
    append(saida, LARGURA_MAX_CABECALHO - 2, "─");
    saida.append("╯");

    return saida;
}

#endif //TERMINAL_HEADER_H
