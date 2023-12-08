#include "Arena.h"

Arena::Arena(Config* config) {
    this->config = config;
    textureGround = LoadTextureRAW("models/textures.bmp");
}

matrix4f Arena::getEixoDeCaida() const {
    return matrix4f::identity();
}

void Arena::draw() const {
    DisplayPlane(textureGround, config->arenaAltura, config->arenaLargura, 0);
}
