#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>

#include "Game.h"
#include "Utilidades.h"
#include "Text.h"

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
                Utilidades::chance(0.1f, 1)
        );

        barris.push_back(barril);
    }

    for (std::vector<Bala*>::iterator it = balas.begin(); it != balas.end();) {
        Bala* bala = *it;
        bala->Mover(dt);

        Vector3f p = bala->posicao;

        // remover balas que sairam da arena
        if (p.x < -config->arenaLargura / 2.0f ||
            p.x > config->arenaLargura / 2.0f ||
            p.y < -config->arenaAltura / 2.0f ||
            p.y > config->arenaAltura / 2.0f) {
            delete bala;
            it = balas.erase(it);
        } else {
            ++it;
        }
    }

    for (std::vector<Barril*>::iterator it = barris.begin(); it != barris.end(); ++it) {
        Barril* barril = *it;

        if (!barril->temInimigo) {
            continue;
        }

        if (Utilidades::chance(1.0f, barril->tempoDesdeUltimoTiro)) {
            Vector3f posicao = barril->getArmaPosicao();
            Vector3f direcao = jogador->getPosicaoAbsolutaCOM() - posicao;
            direcao.normalize();
            float xy = sqrtf(direcao.x * direcao.x + direcao.y * direcao.y);

            // restringe o angulo de tiro. +90 depende do modelo
            float limite = 15;
            float angle = atan2(direcao.y, direcao.x) * 180.0f / M_PI;
            if (angle < -90 - limite) {
                angle = -90 - limite;
            } else if (angle > -90 + limite) {
                angle = -90 + limite;
            }

            angle *= M_PI / 180.0f;

            direcao = Vector3f(xy * cosf(angle), xy * sinf(angle), direcao.z) * config->inimigoVelocidadeTiro;

            Bala* bala = new Bala(
                    posicao,
                    direcao,
                    false
            );

            balas.push_back(bala);
            barril->tempoDesdeUltimoTiro = 0.0f;
        } else {
            barril->tempoDesdeUltimoTiro += dt;
        }
    }

    if (jogador->jogando()) {
        // colisão jogador x barril
        for (std::vector<Barril*>::iterator it = barris.begin(); it != barris.end(); ++it) {
            Barril* barril = *it;

            if (Utilidades::colisaoEsfera(
                    jogador->getCentroDeColisao(),
                    jogador->raioColisao,
                    barril->posicao,
                    barril->raioColisao
            )) {
                printf("Jogador morreu!\n");
                jogador->morrer();
            }
        }

        // colisão de balas
        for (std::vector<Bala*>::iterator it = balas.begin(); it != balas.end(); ++it) {
            Bala* bala = *it;

            if (!bala->veioDoJogador) {
                if (Utilidades::colisaoEsfera(
                        jogador->getCentroDeColisao(),
                        jogador->raioColisao,
                        bala->posicao,
                        bala->raioColisao
                )) {
                    printf("Jogador morreu!\n");
                    jogador->morrer();
                }
            } else {
                for (std::vector<Barril*>::iterator it2 = barris.begin(); it2 != barris.end(); ++it2) {
                    Barril* barril = *it2;

                    if (Utilidades::colisaoEsfera(
                            barril->getCentroDeColisao(),
                            barril->raioColisao,
                            bala->posicao,
                            bala->raioColisao
                    )) {
                        if (barril->temInimigo) {
                            // leva-se um tiro para matar o inimigo
                            barril->temInimigo = false;
                        } else {
                            barril->tempoDesdeUltimoTiro = 0.0f;
                            barril->vida--;

                            if (barril->vida <= 0) {
                                // remover barril
                                delete barril;
                                it2 = barris.erase(it2);
                            }
                        }

                        delete bala;
                        it = balas.erase(it);
                        break;
                    }
                }
            }
        }

        jogador->mover(arena->getEixoDeCaida(), dt);
    }

    // considerando que só o centro do jogador deve estar dentro do mundo
    Vector3f p = jogador->posicao;
    if (p.x > config->arenaLargura / 2.0f) {
        jogador->posicao.x = config->arenaLargura / 2.0f;
    } else if (p.x < -config->arenaLargura / 2.0f) {
        jogador->posicao.x = -config->arenaLargura / 2.0f;
    }

    if (p.y > config->arenaAltura / 2.0f) {
        jogador->posicao.y = config->arenaAltura / 2.0f;
    } else if (p.y < -config->arenaAltura / 2.0f) {
        jogador->posicao.y = -config->arenaAltura / 2.0f;
    }

    glutPostRedisplay();
    tempoDesdeUltimoIdle = t;
}

void Game::display() const {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 0.5, 2000);
    glMatrixMode(GL_MODELVIEW);

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

    if (!jogador->morreu)
        jogador->draw(jogadorScale);

    arena->draw();

    for (std::vector<Bala*>::const_iterator it = balas.begin(); it != balas.end(); ++it) {
        (*it)->draw();
    }

    for (std::vector<Barril*>::const_iterator it = barris.begin(); it != barris.end(); ++it) {
        (*it)->draw(jogador);
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    drawSimpleAxis();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glTranslatef(500, 500, 0);
    glScalef(100, 100, 1);
    glTranslatef(-4.5f, -0.5f, 0);

    if (jogador->morreu) {
        Text::drawText("GAME OVER");
    } else if (jogador->ganhou) {
        Text::drawText("GANHOU");
    }

    glDisable(GL_TEXTURE_2D);

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

    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state != GLUT_DOWN) {
                break;
            }

            if (!jogador->jogando()) {
                break;
            }

            Vector3f posicao = jogador->getPosicaoAbsolutaDaMira();
            Vector3f direcao = camera.getDirection();
            direcao.z = 0.0f;

            direcao.normalize();

            Bala* bala = new Bala(
                    posicao,
                    direcao * config->inimigoVelocidadeTiro,
                    true
            );

            balas.push_back(bala);
            break;
    }
}

void Game::onMouseMove(int x, int y) {
    camera.onMouseMove(x, y);
}

void Game::onReshape(int w, int h) {
    camera.onReshape(w, h);
}

void Game::onMousePassive(int x, int y) {
    camera.onMousePassive(x, y);
}
