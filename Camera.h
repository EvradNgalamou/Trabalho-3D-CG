//
// Created by gibbs2b on 08/12/23.
//

#ifndef TRABALHO_3D_CG_CAMERA_H
#define TRABALHO_3D_CG_CAMERA_H

#include "GL/gl.h"
#include "Jogador.h"

class Camera {
    GLfloat camDist = 50;

    // Angulos de rotação da camera
    GLfloat horizontalAngle = 0; // horizontal
    GLfloat verticalAngle = 0; // vertical

    int toggleCam = 0;
    int camAngle = 60;
    int lastX = 0;
    int lastY = 0;

    // A camera só move se o botão esquerdo do mouse estiver pressionado
    int buttonDown = 0;

public:
    int tipoCamera = 3; // 1, 2, 3

    void onMouseKey(int button, int state, int x, int y);

    void onMouseMove(int x, int y);

    void onReshape(int w, int h);

    // faz as devidas transformações com GL dependendo do tipo de camera atual
    void transform(Jogador* jogador) const;
};


#endif //TRABALHO_3D_CG_CAMERA_H
