# include "volumes.h"

void DrawAxes(double size){

    GLfloat mat_ambient_r[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient_g[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_ambient_b[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
            no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);

    //x axis red
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, 
                mat_ambient_r);
        glColor3fv(mat_ambient_r);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix();

    //y axis green
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, 
                mat_ambient_g);
        glColor3fv(mat_ambient_g);
        glRotatef(90,0,0,1);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix();

    //z axis blue
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_b);
        glColor3fv(mat_ambient_b);
        glRotatef(-90,0,1,0);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix();    
}

void drawSimpleAxisLine(float x, float y, float z) {
    glColor3f(x, y, z);
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3f(x, y, z);
    glEnd();
}

void drawSimpleAxis() {
    // garante que os eixos sempre serao desenhados por cima de tudo
    glClear(GL_DEPTH_BUFFER_BIT);

    float s = 50;

    drawSimpleAxisLine(s, 0, 0);
    drawSimpleAxisLine(0, s, 0);
    drawSimpleAxisLine(0, 0, s);
}

void DrawSolideCube (double size){

   GLfloat materialEmission[] = { 0.00, 0.00, 0.00, 1.0};
   GLfloat materialColor[] = { 1.0, 1.0, 0.0, 1.0};
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = { 128 };
   glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
   glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glColor3f(1,0,0);
   glutSolidCube(size);

}

void DrawSolideSphere (double radius , GLint slices , GLint stacks){

   GLfloat materialEmission[] = { 0.00, 0.00, 0.00, 1.0};
   GLfloat materialColor[] = { 1.0, 1.0, 0.0, 1.0};
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = { 128 };
   glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
   glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glColor3f(1,0,0);
   glutSolidSphere(radius,slices,stacks);
}

void DisplayPlane (GLuint texture, GLfloat Dx, GLfloat Dy, GLfloat Dz){
    GLfloat X = Dx/2;
    GLfloat Y = Dy/2;
    GLfloat Z = Dz/2;

    GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
    GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
    GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 100.0 };
    glColor3f(1,1,1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT  );//X
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );//Y

    glBindTexture (GL_TEXTURE_2D, texture);
    double textureS = 1; // Bigger than 1, repeat
    glBegin (GL_QUADS);
        glNormal3f(0,0,1);
        glTexCoord2f (0, 0);
        glVertex3f (-X,-Y,0);
        glNormal3f(0,0,1);
        glTexCoord2f (0, textureS);
        glVertex3f (X,-Y,0);
        glNormal3f(0,0,1);
        glTexCoord2f (textureS, textureS);
        glVertex3f (X,Y,0);
        glNormal3f(0,0,1);
        glTexCoord2f (textureS, 0);
        glVertex3f (-X,Y,0);
    glEnd();

}

GLuint LoadTextureRAW( const char * filename ){

    GLuint texture;
    
    Image* image = loadBMP(filename);

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
//    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                             0,                            //0 for now
                             GL_RGB,                       //Format OpenGL uses for image
                             image->width, image->height,  //Width and height
                             0,                            //The border of the image
                             GL_RGB, //GL_RGB, because pixels are stored in RGB format
                             GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                               //as unsigned numbers
                             image->pixels);               //The actual pixel data
    delete image;

    return texture;
}

void DesenhaJogadorDeTeste()
{
    // Desenhar Jogador
    glPushMatrix();

    // Corpo Do Jogador
    glPushMatrix();
    glColor3f(0, 1, 0); // Verde
    glTranslatef(0, 0, 6);
    glScalef(2, 1, 4);
    glutSolidCube(1);
    glPopMatrix();
    glVertex3f(1, 0, 0);

    // Perna Esquerda
    glPushMatrix();
    glTranslatef(-1, 0, 2);
    glScalef(1, 1, 4);
    glutSolidCube(1);
    glPopMatrix();

    // Perna direita
    glPushMatrix();
    glTranslatef(1, 0, 2);
    glScalef(1, 1, 4);
    glutSolidCube(1);
    glPopMatrix();

    // Desenho Arma
    glPushMatrix();
    glTranslatef(2, 1, 6);
    glScalef(0.5, 4, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}
