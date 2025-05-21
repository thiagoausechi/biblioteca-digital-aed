#ifndef AUTOR_NAO_EXISTE_H
#define AUTOR_NAO_EXISTE_H
#include <exception>
#include <string>

class AutorNaoExiste final : public std::exception {
    int _id_autor;

public:
    explicit AutorNaoExiste(int id_autor) : _id_autor(id_autor) { ; }

    [[nodiscard]] const char *what() const noexcept override {
        return ("ID '" + std::to_string(this->_id_autor) + "' do autor não existe.").c_str();
    }
};


#endif //AUTOR_NAO_EXISTE_H
