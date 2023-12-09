#include "Text.h"
#include "volumes.h"

GLuint Text::textureId = 0;
bool Text::loaded = false;

void Text::loadTexture() {
    if (loaded)
        return;

    textureId = LoadTextureRAW("texto-textura.bmp");
    loaded = true;
}

void Text::drawText(const char* string) {
    loadTexture();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//Y

    glBindTexture(GL_TEXTURE_2D, textureId);

    int i = 0;

    glBegin(GL_QUADS);
    {
        while (string[i] != '\0') {
            float x = (float) i;
            char c = string[i++];

            float textureS = (float) (c % 16) / 16.0f;
            float textureT = 1.0f - (float) (int) (c / 16) / 16.0f;

            glTexCoord2f(textureS, textureT);
            glVertex3f(x, 0, 0);

            glTexCoord2f(textureS, textureT + 1.0f / 16.0f);
            glVertex3f(x, 1, 0);

            glTexCoord2f(textureS + 1.0f / 16.0f, textureT + 1.0f / 16.0f);
            glVertex3f(x + 1, 1, 0);

            glTexCoord2f(textureS + 1.0f / 16.0f, textureT);
            glVertex3f(x + 1, 0, 0);
        }
    }
    glEnd();
}
