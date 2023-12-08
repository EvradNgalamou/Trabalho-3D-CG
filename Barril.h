//
// Created by gibbs2b on 08/12/23.
//

#ifndef BARRIL_H
#define BARRIL_H

#include "vector3f.h"

class Barril {
    int vida;
    bool temInimigo = false;
    Vector3f posicao;
    Vector3f velocidade;
    float angulo;
    float velocidadeAngular;
    float raioColisao;
    Vector3f miraInimigo;

    void Descer(float dt);

    void atirar(float dt);
};


#endif //BARRIL_H
