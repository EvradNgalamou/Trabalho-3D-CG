#include "Arena.h"

Arena::Arena(Config* config) {
    // TODO: Carregar inclinação pela configuração?
    inclinacao = 5 * (float) M_PI / 180;

    textureGround = LoadTextureRAW("models/textures.bmp");
}

matrix4f Arena::getEixoDeCaida() const {
    matrix4f eixos;
    eixos.rotateX(inclinacao);
    return eixos;
}

void Arena::draw() const {
    glPushMatrix();
    {
        glRotated(inclinacao, 1, 0, 0);
        DisplayPlane(textureGround, arenaLarg, arenaComp, 0);
    }
    glPopMatrix();
}
