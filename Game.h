#ifndef TRABALHO_3D_CG_GAME_H
#define TRABALHO_3D_CG_GAME_H

#include "Jogador.h"

class Game {
    int tipoCamera = 1;

public:
    Jogador* jogador;

    Game() {
        jogador = new Jogador();
    }
};

#endif //TRABALHO_3D_CG_GAME_H
