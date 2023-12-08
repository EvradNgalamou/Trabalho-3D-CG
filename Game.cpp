#include "Game.h"

Game::Game(Config* config) {
    this->config = config;
    arena = new Arena(config);
    jogador = new Jogador(config);
}

void Game::idle() {
    // tempo desde o ultimo idle em segundos
    float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = t - tempoDesdeUltimoIdle;

    jogador->mover(arena->getEixoDeCaida(), dt);

    glutPostRedisplay();
    tempoDesdeUltimoIdle = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
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

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_TEXTURE_2D);

    jogador->draw();

    /* EIXOS = X-RED Y-GREEN Z-BLUE  */
    DrawAxes(3);
    arena->draw();

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
