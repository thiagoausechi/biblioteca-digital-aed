#ifndef UTILS_DATE_H
#define UTILS_DATE_H
#include <string>

inline std::string formatar_data(const time_t data) {
    if (data == 0)
        return "";

    const tm *_data = localtime(&data);
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y às %Hh%M", _data);
    return buffer;
}

#endif //UTILS_DATE_H
