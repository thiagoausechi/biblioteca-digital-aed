#ifndef UTF8_STRING_LENGTH_H
#define UTF8_STRING_LENGTH_H

#include <string>

/*
 * Ao utilizar `std::string::size()`, o compilador não sabe se a string é UTF-8 ou não.
 * Portanto, o resultado pode ser diferente do esperado.
 *
 * Por exemplo, a string "é" resultaria em 2 quando utilizado o `std::string::size()`,
 * mas em certos casos o ideal seria contabilizar apenas como 1 character.
 * Esta função resolve esse problema.
 */
inline int utf8_length(const std::string &str) {
    int length = 0;
    for (const char i: str)
        if ((i & 0xC0) != 0x80)
            length++;

    return length;
}

#endif //UTF8_STRING_LENGTH_H
