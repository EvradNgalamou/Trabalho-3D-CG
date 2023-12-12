#ifndef TRABALHO_3D_CG_GAME_H
#define TRABALHO_3D_CG_GAME_H

#include <vector>

#include "Jogador.h"
#include "Arena.h"
#include "Camera.h"
#include "Barril.h"
#include "Bala.h"


class Game {
    int tipoCamera = 1;
    float tempoDesdeUltimoIdle;
    Camera camera;

    float jogadorScale = 1.0f;

    std::vector<Barril*> barris;
    std::vector<Bala*> balas;

public:
    Jogador* jogador;
    Arena* arena;
    Config* config;

    Game(Config* config);

    bool onKeyPress(unsigned char key, int x, int y);

    bool onKeyUp(unsigned char key, int x, int y);

    void onMouseKey(int button, int state, int x, int y);

    void onMouseMove(int x, int y);

    void onMousePassive(int x, int y);

    void onReshape(int w, int h);

    void idle();

    void display() const;
};

#endif //TRABALHO_3D_CG_GAME_H
