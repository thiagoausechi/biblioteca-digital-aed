#ifndef CASO_DE_USO_H
#define CASO_DE_USO_H

template<typename TResposta = void, typename TPedido = void>
class abstract CasoDeUso {
public:
    virtual ~CasoDeUso() = default;

    virtual TResposta executar(TPedido pedido) = 0;
};

#endif //CASO_DE_USO_H
