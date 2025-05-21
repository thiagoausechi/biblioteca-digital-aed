#ifndef CIDADE_NAO_EXISTE_H
#define CIDADE_NAO_EXISTE_H
#include <exception>
#include <string>

class CidadeNaoExiste final : public std::exception {
    int _id_cidade;

public:
    explicit CidadeNaoExiste(int id_cidade) : _id_cidade(id_cidade) { ; }

    [[nodiscard]] const char *what() const noexcept override {
        return ("ID '" + std::to_string(this->_id_cidade) + "' de cidade não existe.").c_str();
    }
};
#endif //CIDADE_NAO_EXISTE_H
