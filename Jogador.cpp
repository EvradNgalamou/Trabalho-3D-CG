#include <cstdio>
#include "Jogador.h"

void Jogador::mover(matrix4f arena, float dt) {
    if (movX == 0 && movY == 0) {
        return;
    }

    Vector3f movimento(movX, movY, 0);
    movimento.normalize();

    Vector3f velocidade = arena * movimento * config->jogadorVelocidade;
    posicao += velocidade * dt;
}

Jogador::Jogador(Config* config) {
    this->config = config;

    posicao = Vector3f(0.0f, 0.0f, 0.0f);

    movX = 0;
    movY = 0;
}

// TODO: Atualizar com o modelo do jogador

Vector3f Jogador::getPosicaoAbsolutaDosOlhos() const {
    return getPosicaoAbsolutaCOM() + Vector3f(0.0f, 0.0f, 3.0f);
}

Vector3f Jogador::getPosicaoAbsolutaDaMira() const {
    return getPosicaoAbsolutaCOM() + Vector3f(0.0f, 1.0f, 2.0f);
}

Vector3f Jogador::getPosicaoAbsolutaCOM() const {
    return posicao + Vector3f(0.0f, 0.0f, 4.0f);
}
