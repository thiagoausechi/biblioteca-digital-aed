#ifndef EDITORA_NAO_EXISTE_H
#define EDITORA_NAO_EXISTE_H
#include <exception>
#include <string>

class EditoraNaoExiste final : public std::exception {
    int _id_editora;

public:
    explicit EditoraNaoExiste(int id_editora) : _id_editora(id_editora) { ; }

    [[nodiscard]] const char *what() const noexcept override {
        return ("ID '" + std::to_string(this->_id_editora) + "' de editora não existe.").c_str();
    }
};

#endif //EDITORA_NAO_EXISTE_H
