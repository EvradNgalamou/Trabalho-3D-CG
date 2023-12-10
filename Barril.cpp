#include "Barril.h"
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "volumes.h"

void Barril::Descer(float dt) {
    // Transladar na Superficia da Arena
    posicao += velocidade * dt;
    // Rotacionar
    angulo += velocidadeAngular * dt;
}

void Barril::atirar(float dt) {
}

void Barril::draw(Jogador* jogador) const {
    glPushMatrix();
    {
        glTranslatef(posicao.x, posicao.y, posicao.z);
        glScaled(config->barrilAltura, config->barrilLargura, config->barrilLargura);
        glRotatef(angulo, 1, 0, 0);

        // TODO: Desenhar modelo do barril
        glColor3f(0.647059f, 0.164706f, 0.164706f);
        glutSolidCube(1.0f);
    }
    glPopMatrix();

    if (temInimigo) {
        glPushMatrix();
        {
            // todos os inimiogos miram no jogador
            float angulo = atan2(
                    jogador->posicao.y - posicao.y,
                    jogador->posicao.x - posicao.x
            ) * 180 / M_PI;

            // limite de -60 a 60 graus
            if (angulo < -90 - 60.0f) {
                angulo = -90 - 60.0f;
            } else if (angulo > -90 + 60.0f) {
                angulo = -90 + 60.0f;
            }

            glTranslatef(posicao.x, posicao.y, posicao.z);
            glTranslatef(0.0f, 0.0f, config->barrilLargura / 2.0f);
            glScalef(config->inimigoRaioCabeca, config->inimigoRaioCabeca, config->inimigoRaioCabeca);
            glRotatef(angulo, 0, 0, 1);
            // ajuste que depende do modelo. O teste olha para o y
            glRotatef(90 + 180, 0, 0, 1);
            glColor3f(1, 0, 0);
            DesenhaJogadorDeTeste();
        }
        glPopMatrix();
    }
}

Barril::Barril(Config* config, Vector3f posicao, Vector3f velocidade, bool temInimigo) {
    vida = config->barrilNumeroTiros;
    this->config = config;
    this->posicao = posicao;
    this->velocidade = velocidade;
    this->temInimigo = temInimigo;
    this->angulo = 0.0f;
    float a = config->barrilAltura / 2.0f;
    float b = config->barrilLargura / 2.0f;
    this->raioColisao = sqrtf(a * a + b * b) * 2;
    this->miraInimigo = Vector3f(0.0f, 0.0f, 0.0f);

    this->velocidadeAngular = (config->barrilVelocidade / (config->barrilLargura / 2.0f)) * 180.0f / M_PIf;
}

Vector3f Barril::getCentroDeColisao() const {
    Vector3f v = posicao + Vector3f(0.0f, 0.0f, config->barrilLargura / 2.0f);

    if (temInimigo)
        v.z += config->inimigoRaioCabeca * 8;

    return v;
}
