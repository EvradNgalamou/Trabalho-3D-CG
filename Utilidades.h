#ifndef TRABALHO_3D_CG_UTILIDADES_H
#define TRABALHO_3D_CG_UTILIDADES_H

#include "vector3f.h"


class Utilidades {

public:
    static bool chance(float chance, float dt);

    static float randomf();

    static bool colisaoEsfera(Vector3f p1, float r1, Vector3f p2, float r2) {
        return (p2 - p1).lengthSqr() < (r1 + r2) * (r1 + r2);
    }
};


#endif //TRABALHO_3D_CG_UTILIDADES_H
