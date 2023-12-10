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

public:
    float raioColisao;
    bool morreu;
    bool ganhou;
    int pontuacao;

    int movX;
    int movY;

    Vector3f posicao;

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

    Vector3f getCentroDeColisao() const;

    void draw(float scale) const;

    bool jogando() const;

    void morrer();
};

#endif //JOGADOR_H
