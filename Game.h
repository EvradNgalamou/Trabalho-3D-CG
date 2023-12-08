#ifndef TRABALHO_3D_CG_GAME_H
#define TRABALHO_3D_CG_GAME_H

#include "Jogador.h"
#include "Arena.h"
#include "Camera.h"

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

        // Adicionar Barril
        if jogando && dt * random() < 10% // 10%/segundo de adicionar um barril
            add barril
                x = random
                y = topo y da arena
                z = topo z da arena
                velocidade = velocidade das configurações * direção para baixo da arena // lembrando que a arena é inclinada

        // Bala Sair da Arena
        foreach bala
            if bala saiu da arena
                remove bala

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
            // Barril Com Inimigo Sair da Arena
            // Barril Sair Da Arena
            //    Destroir o Barril
            if barril tem inimigo e ambos o barril e inimigo sairam da arena
                remove barril
            else if barril não tem inimigo e saiu da arena
                remove barril

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

        // vou considerar que só o centro do jogador deve estar dentro do mundo
        if px < min x
            px = min x
        else if px < max x
            px = max x

        if py < min y
            py = min y
        else if py < max y
            py = max y

        if pz < min z
            pz = min z
        else if pz < max z
            pz = max z

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

public:
    Jogador* jogador;
    Arena* arena;
    Config* config;

    Game(Config* config);

    bool onKeyPress(unsigned char key, int x, int y);

    bool onKeyUp(unsigned char key, int x, int y);

    void onMouseKey(int button, int state, int x, int y);

    void onMouseMove(int x, int y);

    void onReshape(int w, int h);

    void idle();

    void display() const;
};

#endif //TRABALHO_3D_CG_GAME_H
