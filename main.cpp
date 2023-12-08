#include <cstdlib>
#include <cstdio>
#include <ctime>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "objloader.h"

#include "volumes.h"

#include "Config.h"
#include "Game.h"
#include "Camera.h"

// Key status
int keyStatus[256];

//Camera controls
Config c;

mesh gBarril;

Camera camera;
Game *g;
void DesenhaJogador()
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
        glTranslatef(2, 0, 6);
        glScalef(0.5, 4, 0.5);
        glutSolidCube(1);
        glPopMatrix();

        glPopMatrix();
    }

/* TECLADO*/
void keyPress(unsigned char key, int x, int y){
/*
    keyStatus[(int)(key)] = 1;
    glutPostRedisplay();

*/
    switch (key){
        case '1':
            camera.tipoCamera = 1;
            break;
        case '2':
            camera.tipoCamera = 2;
            break;
        case '3':
            camera.tipoCamera = 3;
            break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}
void keyUp(unsigned char key, int x, int y){

    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}
void ResetKeyStatus(){

    int i;
    // Initialize keyStatus
    for (i = 0; i < 256; i++)
        keyStatus[i] = 0;
}

/* MOUSE */
void mouse_callback(int button, int state, int x, int y){
    camera.onMouseDown(button, state, x, y);
}

void mouse_motion(int x, int y){
    camera.onMouseMove(x, y);
}

void passivemove(int x, int y) {}

void reshape (int w, int h) {
    camera.onReshape(w, h);
}


void init()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);

    ResetKeyStatus();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 15);

    gBarril.loadMesh("models/arena.obj");
    gBarril.loadTexture("models/textures.bmp");

    g = new Game(&c);
}

float gTempoDesdeUltimoIdle = 0;

void idle(void)
{

    // tempo desde o ultimo idle em segundos
    float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = 0.001f * (glutGet(GLUT_ELAPSED_TIME) - gTempoDesdeUltimoIdle);
    glutPostRedisplay();

    gTempoDesdeUltimoIdle = glutGet(GLUT_ELAPSED_TIME);
}

void display(){
    
    /* Limpar todos os pixels  */
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f); // AZUL, no opacity(alpha).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.transform(g->jogador);


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // TODO: Desenhar coisas afetadas por luz

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_TEXTURE_2D);




    drawSimpleAxis();
   
    gBarril.draw();

    /* EIXOS = X-RED Y-GREEN Z-BLUE  */
    DrawAxes(3);
    g->arena->draw();

    /* Desenhar no frame buffer! */
    glutSwapBuffers(); // Funcao apropriada para janela double buffer
}

int main(int argc, char *argv[])
{
    Config::load(&c);

    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Create the window.
    glutInitWindowSize(c.arenaLargura, c.arenaAltura);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("Quebrador de Barrils");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
//    glutMouseFunc(mouse);
    glutMouseFunc(mouse_callback);
    glutMotionFunc(mouse_motion);
    glutReshapeFunc (reshape);
    glutPassiveMotionFunc(passivemove);
    glutIdleFunc(idle);
    init();
    glutMainLoop();

    return 0;
}

