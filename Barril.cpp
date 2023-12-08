//
// Created by gibbs2b on 08/12/23.
//

#include "Barril.h"

void Barril::Descer(float dt) {
    // Transladar na Superficia da Arena
    posicao += velocidade * dt;
    // Rotacionar
    angulo += velocidadeAngular * dt;
}

void Barril::atirar(float dt) {
}
