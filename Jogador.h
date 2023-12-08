#ifndef JOGADOR_H
#define JOGADOR_H

#include "matrix4f.h"
#include "vector3f.h"
#include "Config.h"

/*
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
};

#endif //JOGADOR_H
