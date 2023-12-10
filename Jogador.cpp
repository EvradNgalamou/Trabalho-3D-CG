#include "Jogador.h"
#include "volumes.h"

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

    // 4 vem do modelo (8 de altura)
    raioColisao = config->jogadorRaioCabeca * 4.0f;
}

// TODO: Atualizar com o modelo do jogador

Vector3f Jogador::getPosicaoAbsolutaDosOlhos() const {
    return getPosicaoAbsolutaCOM() + Vector3f(0.0f, 0.0f, 3.0f * config->jogadorRaioCabeca);
}

Vector3f Jogador::getPosicaoAbsolutaDaMira() const {
    return getPosicaoAbsolutaCOM() + Vector3f(0.0f, 1.0f, 2.0f) * config->jogadorRaioCabeca;
}

Vector3f Jogador::getPosicaoAbsolutaCOM() const {
    return posicao + Vector3f(0.0f, 0.0f, 4.0f * config->jogadorRaioCabeca);
}

void Jogador::draw(float scale) const {
    float s = config->jogadorRaioCabeca * scale;

    glPushMatrix();
    {
        glTranslatef(posicao.x, posicao.y, posicao.z);
        glScalef(s, s, s);
        DesenhaJogadorDeTeste();
    }
    glPopMatrix();
}

bool Jogador::jogando() const {
    return !morreu && !ganhou;
}

void Jogador::morrer() {
    morreu = true;
}

Vector3f Jogador::getCentroDeColisao() const {
    return getPosicaoAbsolutaCOM();
}
