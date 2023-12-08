#ifndef TRABALHO_3D_CG_ARENA_H
#define TRABALHO_3D_CG_ARENA_H

#include <cmath>
#include <GL/gl.h>
#include "matrix4f.h"
#include "Config.h"
#include "volumes.h"

class Arena {
    Config* config;

public:
    /* Identificadores de textura */
    GLuint textureGround;//.................. Piso do cenario

    /* Define parametro padrao para os objetos */

    Arena(Config* config);

    matrix4f getEixoDeCaida() const;

    void draw() const;
};


#endif //TRABALHO_3D_CG_ARENA_H
