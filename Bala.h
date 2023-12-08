#ifndef TRABALHO_3D_CG_BALA_H
#define TRABALHO_3D_CG_BALA_H

#include "vector3f.h"

class Bala {
public:
    Vector3f posicao;
    Vector3f velocidade;
    bool veioDoJogador;
    float raioColisao;

    Bala(Vector3f posicao, Vector3f velocidade, bool veioDoJogador);

    void Mover(float dt);

    void draw() const;
};


#endif //TRABALHO_3D_CG_BALA_H
