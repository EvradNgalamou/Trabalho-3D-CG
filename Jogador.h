#ifndef JOGADOR_H
#define JOGADOR_H

#include "vector3f.h"

/*
    campos
        posição
        // velocidade
        raio de colisão
        morreu? // bool
        ganhou?
        pontuação

        // direção do movimento em relação às teclas. Note que z não tem pois não tem um movimento para cima como pular.
        // Essa direção depois será convertida para um vetor 3D que considera a inclinação da arena. Só pensar assim:
        // (0,0) é parado, (-1,0) é indo para esquerda, (0,1) cima, (1,1) diagonal, etc.
        movimento: x e y // tem que ser int

    funções/métodos:
    mover jogador(dt)
        if movimento é (0,0)
            return

        direção da velocidade = (base da arena, matrix 3x3) * (movimento [x, y, 0], vetor)
        velocidade = (velocidade configurada no XML, scalar) * direção da velocidade normalizada
        posição += velocidade * dt

    posição da arma
        return posição do jogador + posição da arma relativa ao jogador

    posição relativa da arma
        // depende do modelo. Exemplo: a origem do jogador será os pés, mas os pés são relativos ao corpo (recomendado)
        posição do tronco (~centro de gravidade) + posição do braço + posição do ante-braço + posição da arma relativa à mão

    jogando: bool
        return ainda não morreu and não morreu

    desenhar
        push matrix
            translate to posição

            // depende do modelo, mas vou assumir que o corpo do jogador será dividido em dois a partir do centro de gravidade do
            // jogador, que é próximo ao umbigo
            translate ao centro do jogador
            desenhar modelo da parte inferior // assumindo que o umbigo é a origem do modelo

            // gambiarra
            look at
                eye = (0,0,0)
                at = direção da mira do jogador
                up = (0,0,1)

            // assumindo que o umbigo é a origem do modelo
            // também estou assumindo que a arma já está no modelo, logo o corpo está "mirando" na mesma direção da arma
            desenhar modelo da parte superior

    posição do olho do jogador nas coordenadas do mundo
        posição do jogador + centro de gravidade do jogador + posição do olho relativo ao modelo
 * */

class Jogador {
    Vector3f posicao;
    float raioColisao;
    bool morreu;
    bool ganhou;
    int pontuacao;
    int movX;
    int movY;

public:
    void mover(float dt);

    // TODO: Atualizar com o modelo do jogador

    Vector3f getPosicaoAbsolutaDosOlhos() const {
        return getPosicaoAbsolutaCOM() + Vector3f(0.0f, 0.0f, 3.0f);
    }

    Vector3f getPosicaoAbsolutaDaMira() const {
        return getPosicaoAbsolutaCOM() + Vector3f(0.0f, 1.0f, 2.0f);
    }

    // COM = center of mass, centro de gravidade
    Vector3f getPosicaoAbsolutaCOM() const {
        return posicao + Vector3f(0.0f, 0.0f, 4.0f);
    }
};

#endif //JOGADOR_H
