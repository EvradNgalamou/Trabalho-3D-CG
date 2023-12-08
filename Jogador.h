#ifndef JOGADOR_H
#define JOGADOR_H

#include "matrix4f.h"
#include "vector3f.h"
#include "Config.h"

/*
    jogando: bool
        return ainda não morreu and não morreu
 * */

class Jogador {
    Config* config;

    Vector3f posicao;
    float raioColisao;
    bool morreu;
    bool ganhou;
    int pontuacao;

public:
    int movX;
    int movY;

    Jogador(Config* config);

    /**
     * A matriz da arena é uma matriz base (conceito de algebra linear, não confundir com base da arena). Existe uma
     * matriz de eixos na classe da arena.
     */
    void mover(matrix4f arena, float dt);

    Vector3f getPosicaoAbsolutaDosOlhos() const;

    Vector3f getPosicaoAbsolutaDaMira() const;

    // COM = center of mass, centro de gravidade
    Vector3f getPosicaoAbsolutaCOM() const;

    void draw() const;
};

#endif //JOGADOR_H
