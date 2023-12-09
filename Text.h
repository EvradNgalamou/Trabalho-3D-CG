#ifndef TRABALHO_3D_CG_TEXT_H
#define TRABALHO_3D_CG_TEXT_H

#include <GL/gl.h>

class Text {
    static GLuint textureId;
    static bool loaded;

    static void loadTexture();

public:
    static void drawText(const char* string);
};


#endif //TRABALHO_3D_CG_TEXT_H
