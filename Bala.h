#ifndef TRABALHO_3D_CG_BALA_H
#define TRABALHO_3D_CG_BALA_H


class Bala {
    /*
    campos:
        posicao
        velocidade
        origem: inimigo ou jogador
        raio de colisão

    funções/métodos:
    Mover Balas
        // Fazer Transladar Bala na Arena
        posição += velocidade * dt

    desenhar
        push matrix
            translate to posição

            m = cria matrix base na direção da bala
            gl multiply 4x4

            desenhar modelo da bala em (0, 0, 0), considerando que está em "pé" na direção (0, 0, 1) (não lembro agora)

    desenhar modelo
        depende do modelo
     */

};


#endif //TRABALHO_3D_CG_BALA_H
