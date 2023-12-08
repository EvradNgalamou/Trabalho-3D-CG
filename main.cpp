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

Game *g;

/* TECLADO*/
void keyPress(unsigned char key, int x, int y){
    keyStatus[(int)(key)] = 1;

    if (g->onKeyPress(key, x, y))
        return;

    switch (key){
        case 27 :
             exit(0);
    }

    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y){

    keyStatus[(int)(key)] = 0;

    if (g->onKeyUp(key, x, y))
        return;

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
    g->onMouseKey(button, state, x, y);
}

void mouse_motion(int x, int y){
    g->onMouseMove(x, y);
}

void passivemove(int x, int y) {}

void reshape (int w, int h) {
    g->onReshape(w, h);
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

void idle(void)
{
    g->idle();
}

void display(){
    g->display();
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

