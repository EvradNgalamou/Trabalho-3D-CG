//
// Created by gibbs2b on 08/12/23.
//

#ifndef JOGADOR_H
#define JOGADOR_H

#include "vector3f.h"

class Jogador {
    Vector3f posicao;
    float raioColisao;
    bool morreu;
    bool ganhou;
    int pontuacao;
    int movX;
    int movY;

public:
    void mover(float dt);

    // TODO: Atualizar com o modelo do jogador

    Vector3f getPosicaoAbsolutaDosOlhos() const {
        return getPosicaoAbsolutaCOM() + Vector3f(0.0f, 0.0f, 3.0f);
    }

    Vector3f getPosicaoAbsolutaDaMira() const {
        return getPosicaoAbsolutaCOM() + Vector3f(0.0f, 1.0f, 2.0f);
    }

    // COM = center of mass, centro de gravidade
    Vector3f getPosicaoAbsolutaCOM() const {
        return posicao + Vector3f(0.0f, 0.0f, 4.0f);
    }
};

#endif //JOGADOR_H
