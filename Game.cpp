#include "Game.h"

Game::Game(Config* config) {
    this->config = config;
    arena = new Arena(config);
    jogador = new Jogador(config);
}
