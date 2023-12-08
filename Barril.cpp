#include "Barril.h"
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void Barril::Descer(float dt) {
    // Transladar na Superficia da Arena
    posicao += velocidade * dt;
    // Rotacionar
    angulo += velocidadeAngular * dt;
}

void Barril::atirar(float dt) {
}

void Barril::draw() const {
    glPushMatrix();
    {
        glTranslatef(posicao.x, posicao.y, posicao.z);
        glScaled(config->barrilAltura, config->barrilLargura, config->barrilLargura);
        glRotatef(angulo, 1, 0, 0);

        // TODO: Desenhar modelo do barril
        glColor3f(0.5f, 0.5f, 0.5f);
        glutSolidCube(1.0f);

        // TODO: Desenhar modelo do jogador
        if (temInimigo) {
        }
    }
    glPopMatrix();
}

Barril::Barril(Config* config, Vector3f posicao, Vector3f velocidade, bool temInimigo) {
    this->config = config;
    this->posicao = posicao;
    this->velocidade = velocidade;
    this->temInimigo = temInimigo;
    this->angulo = 0.0f;
    this->raioColisao = config->barrilLargura;
    this->miraInimigo = Vector3f(0.0f, 0.0f, 0.0f);

    this->velocidadeAngular = (config->barrilVelocidade / (config->barrilLargura / 2)) * 180 / M_PI;
}
