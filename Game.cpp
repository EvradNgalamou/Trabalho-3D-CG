#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>

#include "Game.h"
#include "Utilidades.h"

Game::Game(Config* config) {
    this->config = config;
    arena = new Arena(config);
    jogador = new Jogador(config);

    jogador->posicao.y = -config->arenaAltura / 4.0f;
}

void Game::idle() {
    // tempo desde o ultimo idle em segundos
    float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = t - tempoDesdeUltimoIdle;

    for (std::vector<Barril*>::iterator it = barris.begin(); it != barris.end(); ++it) {
        (*it)->Descer(dt);
    }

    // remover barris que sairam da arena
    for (std::vector<Barril*>::iterator it = barris.begin(); it != barris.end();) {
        Barril* barril = *it;
        if (barril->posicao.y + barril->raioColisao < -config->arenaAltura / 2.0f) {
            delete barril;
            it = barris.erase(it);
        } else {
            ++it;
        }
    }

    // 120%/segundo de adicionar um barril
    if (jogador->jogando() && Utilidades::chance(1.20f, dt)) {
        float x = Utilidades::randomf() * config->arenaLargura - config->arenaLargura / 2;
        Barril* barril = new Barril(
                config,
                Vector3f(x, config->arenaAltura / 2, config->barrilLargura / 2),
                Vector3f(0.0f, -config->barrilVelocidade, 0.0f),
                dt * rand() < 0.1f // 10% de chance de ter inimigo
        );

        barris.push_back(barril);
    }

    jogador->mover(arena->getEixoDeCaida(), dt);

    glutPostRedisplay();
    tempoDesdeUltimoIdle = t;
}

void Game::display() const {
    /* Limpar todos os pixels  */
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f); // AZUL, no opacity(alpha).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.transform(jogador);


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // TODO: Desenhar coisas afetadas por luz

    jogador->draw();
    arena->draw();

    for (std::vector<Barril*>::const_iterator it = barris.begin(); it != barris.end(); ++it) {
        (*it)->draw();
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_TEXTURE_2D);

    drawSimpleAxis();

    /* Desenhar no frame buffer! */
    glutSwapBuffers(); // Funcao apropriada para janela double buffer
}

bool Game::onKeyPress(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            camera.tipoCamera = 1;
            break;
        case '2':
            camera.tipoCamera = 2;
            break;
        case '3':
            camera.tipoCamera = 3;
            break;

            // movimento do jogador
        case 'a':
            jogador->movX -= 1;
            break;
        case 'd':
            jogador->movX += 1;
            break;
        case 'w':
            jogador->movY += 1;
            break;
        case 's':
            jogador->movY -= 1;
            break;
        default:
            return false;
    }

    return true;
}

bool Game::onKeyUp(unsigned char key, int x, int y) {
    switch (key) {
        // movimento do jogador
        case 'a':
            jogador->movX += 1;
            break;
        case 'd':
            jogador->movX -= 1;
            break;
        case 'w':
            jogador->movY -= 1;
            break;
        case 's':
            jogador->movY += 1;
            break;
        default:
            return false;
    }

    return true;
}

void Game::onMouseKey(int button, int state, int x, int y) {
    camera.onMouseKey(button, state, x, y);
}

void Game::onMouseMove(int x, int y) {
    camera.onMouseMove(x, y);
}

void Game::onReshape(int w, int h) {
    camera.onReshape(w, h);
}
