#ifndef CASO_DE_USO_H
#define CASO_DE_USO_H

template<typename TResposta = void, typename TPedido = void>
class CasoDeUso {
public:
    virtual ~CasoDeUso() = default;

    virtual TResposta executar(TPedido pedido) = 0;
};

// Caso de uso sem um TPedido; Portanto o executar() não recebe parâmetros
template<typename TResposta>
class CasoDeUso<TResposta, void> {
public:
    virtual ~CasoDeUso() = default;

    virtual TResposta executar() = 0;
};

// Caso de uso sem um TResposta e um TPedido; Portanto o executar() não recebe parâmetros e não retorna nada
template<>
class CasoDeUso<void, void> {
public:
    virtual ~CasoDeUso() = default;

    virtual void executar() = 0;
};

#endif //CASO_DE_USO_H
