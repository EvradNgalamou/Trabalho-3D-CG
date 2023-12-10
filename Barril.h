#ifndef BARRIL_H
#define BARRIL_H

#include "vector3f.h"
#include "Jogador.h"
#include "Config.h"

/*
    funções/métodos:
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

 * */

class Barril {
public:
    int vida;
    bool temInimigo = false;
    Vector3f velocidade;
    float angulo;
    float velocidadeAngular;
    Vector3f miraInimigo;
    Config* config;

    float raioColisao;
    Vector3f posicao;

    float tempoDesdeUltimoTiro = 0.0f;

    Barril(Config* config, Vector3f posicao, Vector3f velocidade, bool temInimigo);

    void Descer(float dt);

    void atirar(float dt);

    void draw(Jogador* jogador) const;

    Vector3f getArmaPosicao() const {
        return posicao + Vector3f(0.0f, 0.0f, config->barrilLargura / 2.0f + config->inimigoRaioCabeca * 8);
    }

    Vector3f getCentroDeColisao() const;
};


#endif //BARRIL_H
