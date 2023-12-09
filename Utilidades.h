#ifndef TRABALHO_3D_CG_UTILIDADES_H
#define TRABALHO_3D_CG_UTILIDADES_H

#include "vector3f.h"

/*
    se esfera está dentro da arena
        arena:
            min/max x/y/z // uma caixa
        esfera:
            px/py/pz, raio r

        está dentro
            se min x - r <= px
             e max x + r >= px
             e min y - r <= py
             e max y + r >= py
             e min z - r <= pz
             e max z + r >= pz

    desenhar numero(n)
        // recomendo criar uma imagem para cada número aí você só usa como textura aqui
        foreach digit
            load texture for digit
            darw rectangle of digit

    criar base de matriz 4x4 para cima(direção): float[16]
        // cria uma matrix com uma base na bala. Algebra linear
        axis x = velocidade // cada eixo é um vetor 3D, então apesar de se chamar axis x, axis x tem 3 valores por si
        axis y = axis x * (0, 0, 1) // multiplicação vetorial
        axis z = axis y * axis x // multiplicação vetorial

        // normalize os três eixos
        axis x /= len of axis x
        axis y /= len of axis y
        axis z /= len of axis z

        return 4x4 matrix (column-major ordering)
            [  axis x  axis y  axis z  0 ] // lembrando que são 3 linhas aqui
            [    0       0       0     1 ]

 * */

class Utilidades {

public:
    static bool chance(float chance, float dt);

    static float randomf();

    static bool colisaoEsfera(Vector3f p1, float r1, Vector3f p2, float r2) {
        return (p2 - p1).lengthSqr() < (r1 + r2) * (r1 + r2);
    }
};


#endif //TRABALHO_3D_CG_UTILIDADES_H
