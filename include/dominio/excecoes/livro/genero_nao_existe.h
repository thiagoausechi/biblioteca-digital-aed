#ifndef GENERO_NAO_EXISTE_H
#define GENERO_NAO_EXISTE_H
#include <exception>
#include <string>

class GeneroNaoExiste final : public std::exception {
    int _id_genero;

public:
    explicit GeneroNaoExiste(int id_genero) : _id_genero(id_genero) { ; }

    [[nodiscard]] const char *what() const noexcept override {
        return ("ID '" + std::to_string(this->_id_genero) + "' do gênero não existe.").c_str();
    }
};


#endif //GENERO_NAO_EXISTE_H
