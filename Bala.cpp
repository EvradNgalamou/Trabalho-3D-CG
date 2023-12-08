#include "Bala.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

Bala::Bala(Vector3f posicao, Vector3f velocidade, bool veioDoJogador) {
    this->posicao = posicao;
    this->velocidade = velocidade;
    this->veioDoJogador = veioDoJogador;
    this->raioColisao = 0.1f;
}

void Bala::Mover(float dt) {
    posicao += velocidade * dt;
}

void Bala::draw() const {
    glPushMatrix();
    {
        glTranslatef(posicao.x, posicao.y, posicao.z);
        glScalef(0.1f, 0.1f, 0.1f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glutSolidSphere(1.0f, 10, 10);
    }
    glPopMatrix();
}
