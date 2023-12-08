//
// Created by gibbs2b on 08/12/23.
//

#ifndef JOGADOR_H
#define JOGADOR_H

#include "vector3f.h"

class Jogador
{
    Vector3f posicao;
    float raioColisao;
    bool morreu;
    bool ganhou;
    int pontuacao;
    int movX;
    int movY;

    void mover(float dt);
};

#endif //JOGADOR_H
