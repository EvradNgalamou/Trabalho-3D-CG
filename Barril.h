#ifndef BARRIL_H
#define BARRIL_H

#include "vector3f.h"

/*
    campos:
        vida
        se tem inimigo
        posição
        ângulo do barril // o barril gira quando desce
        velocidade ângular
        raio de colisão
        mira do inimigo // que deve sempre estar mirando para o jogador

    funções/métodos:
    Descer Barril
        // Transladar na Superficia da Arena
        posição += velocidade * dt
        // Rotacionar
        ângulo += velocidade angular * dt

    atirar
        // Tiro aleatorio
        if random() * dt < 10% // 10%/segundo, altere depois para a correta frequência
            return

        // Bala Sair da arma do inimigo em direção a Posição Atual da Cabeça do Jogador
        add bala ao mundo
            posicao = posição da ponta da arma
            velocidade = constante * direção da arma

    update mira(jogador)
        // Sempre apontando na Posição Atual da Cabeça do Jogador
        mira = normalize(jogador.posição - this.posição)

    desenhar
        push matrix
            translate to posição
            push matrix
                rotate angulo do barril
                desenhar modelo do barril, considerando que o modelo está com o eixo de rotação alinhado com o eixo y

            if tem inimigo
                gl translate z = raio do barril // assim o pé ficará no topo do barril
                desenhar modelo do jogador

            gl translate
                x = -largura do barril
                y = raio do barril + spacinho
                z = -raio do barril

            desenhar vida do barril

    desenhar modelo do inimigo
        TODO: corpo do jogador e arma
 * */

class Barril {
    int vida;
    bool temInimigo = false;
    Vector3f posicao;
    Vector3f velocidade;
    float angulo;
    float velocidadeAngular;
    float raioColisao;
    Vector3f miraInimigo;

    void Descer(float dt);

    void atirar(float dt);
};


#endif //BARRIL_H
