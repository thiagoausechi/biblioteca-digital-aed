#ifndef TERMINAL_HEADER_H
#define TERMINAL_HEADER_H

#include <iostream>

inline void append(std::string &source, const int n, const std::string &str_to_append) {
    for (int i = 0; i < n; i++)
        source += str_to_append;
}

#endif //TERMINAL_HEADER_H
