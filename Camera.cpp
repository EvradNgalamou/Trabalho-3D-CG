//
// Created by gibbs2b on 08/12/23.
//

#include "Camera.h"

#include <cmath>
#include <GL/glut.h>

void Camera::onMouseKey(int button, int state, int x, int y) {
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        lastX = x;
        lastY = y;
        buttonDown = 1;
    }
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
        buttonDown = 0;
    }
}

float radian60 = 60 * M_PI / 180.0;

void Camera::onMouseMove(int x, int y) {
    if (!buttonDown)
        return;

    int dx = x - lastX;
    int dy = y - lastY;

    // Os valores são sensibilidade do mouse
    float horizontal = horizontalAngle + 0.007 * dx;
    float vertical = verticalAngle + 0.02 * dy;

    if (vertical < -radian60) {
        vertical = -radian60;
    } else if (vertical > radian60) {
        vertical = radian60;
    }

    horizontalAngle = horizontal;
    verticalAngle = vertical;

    lastX = x;
    lastY = y;
}

void Camera::onReshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camAngle, (GLfloat) w / (GLfloat) h, 1, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

void Camera::transform(Jogador* jogador) const {
    // TODO: Tem que decidir a convenção: y ou z que é cima? Eu recomendo z pois quando se plota o gráfico de uma função
    //  em 3D, o eixo z é o eixo vertical, (x, y) é o plano horizontal

    // coordenadas esféricas
    Vector3f direction(
            cosf(horizontalAngle) * cosf(verticalAngle),
            sinf(horizontalAngle) * cosf(verticalAngle),
            sinf(verticalAngle)
    );
    Vector3f position;

    switch (tipoCamera) {
        case 1:
            position = jogador->getPosicaoAbsolutaDosOlhos();
            break;
        case 2:
            position = jogador->getPosicaoAbsolutaDaMira();
            break;
        case 3:
            position = jogador->getPosicaoAbsolutaCOM() - direction * camDist;
            break;
    }

    Vector3f center = position + direction * camDist;

    gluLookAt(
            position.x, position.y, position.z,
            center.x, center.y, center.z,
            0, 0, 1
    );
}
