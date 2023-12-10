#ifndef TRABALHO_3D_CG_GAME_H
#define TRABALHO_3D_CG_GAME_H

#include <vector>

#include "Jogador.h"
#include "Arena.h"
#include "Camera.h"
#include "Barril.h"
#include "Bala.h"

/*
class jogo/game // seria tipo variáveis globais, mas fica mais organizado dentro de uma classe
    campos
        jogador
        list de barris
        list de balas
        camera atual: 1, 2, 3
        zoom
        noturno

    Idle
        foreach barril
            Descer Barril
        if jogando
            foreach barril
                Inimigo Atira
        foreach bala
            Mover Balas

        Mover Jogador

        // Bala Acertar Jogador
        for each bala
            if bala veio do jogador
                // isso só aconteceria se a velocidade da bala for menor que do jogador.
                // Mas a arma provavelmente estara dentro do raio de colisão do jogador, então inicialmente sempre vai
                // estar colidindo com o jogador até que saia do raio
                continue // bala do jogador não acerta jogador

            if bala colide com jogador // note que isso usa uma das utilidades
                Jogador morre
                // Mensagem de *Game over*
                // Jogo Termina

        // Bala Acertar Inimigo ou barril
        for each barril
            for each bala
                if bala veio de um inimigo
                    continue // bala de inimigo não acerta inimigo

                if barril tem inimigo e bala colide inimigo
                    mata inimigo
                    remove bala

                    pontuação += mata inimigo
                else if bala colide barril
                    diminuir vida
                    remove bala

                    pontuação += acerta barril

            if vida <= 0
                remove barril
                pontuação += destroi barril

        // Jogador Sair Da Arena
        // nem toda parte da arena é jogável no trab 2D. Metade da arena não era acessível
        arena jogável:
            max/min x/y/z
            jogador: px/py/pz, r = raio

        // Verificar se Jogador Ganhou
        if pontuação > mínimo para ganhar
            ganhou = true
            remove todas as balas
            remove todos os barris

        // Mira Do Inimigo
        for each barril
            update mira

    # Display:
        push matrix
            // camera
            if camera 1
                look at
                    eye = posição do olho do jogador nas coordenadas do mundo
                    at = '' + mira da arma
                    up = (0,0,1)

                // TODO: Zoom
            if camera 2
                look at
                    eye = posição da arma do jogador nas coordenadas do mundo
                    at = '' + mira da arma
                    up = (0,0,1)

                // TODO: Zoom
            if camera 3
                look at
                    eye = posição jogador
                    at = posição jogador + mira da arma
                    up = (0,0,1)

                // TODO: Zoom

            foreach barril: desenhar
            foreach bala: desenhar
            desenhar jogador

            Desenhar Arena

            if noturno
                Luz na Arma
            else
                Luz na arena

        push matrix
            gl ortho
                // TODO: tamanho da tela, etc

            if ganhou
                Mensagem Venceu
            if morreu
                Mensagem *Game Over*

            desenhar Pontuação

            gl translate canto inferior direito
            gl scale 1/4
                desenhar Mini Mapa

    on key down
        1, 2, 3: mudar camera

        a: movimento x -= 1
        d: movimento x += 1
        w: movimento y += 1
        s: movimento y -= 1

        +: zoom *= 1.1
        -: zoom /= 1.1

        n: noturno = !noturno

    on key up
        // desfar o movimento do key down
        a: movimento x += 1
        d: movimento x -= 1
        w: movimento y -= 1
        s: movimento y += 1

    on mouse down
        botão esquerdo
            bala = new bala
                posição posição da ponta da arma no mundo
                velocidade = (velocidade configurada) * direção da arma normalizada
            add bala à lista de balas

    on mouse move
        TODO: Mover a Camera

 * */

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
