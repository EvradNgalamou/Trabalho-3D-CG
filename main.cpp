#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tinyxml2.h"
#include "vector3f.h"
#include "objloader.h"
#include "volumes.h"
#include <ctime>

using namespace tinyxml2;

// Key status
int keyStatus[256];

/* Identificadores de textura */
GLuint textureGround;//.................. Piso do cenario

/* Define parametro padrao para os objetos */
GLfloat stdSize   = 1.0; 
GLfloat arenaComp = 10*stdSize; //................ Define o comprimento da arena 
GLfloat arenaLarg = 4*stdSize; //................ Define a largura da arena 

//Camera controls
double camDist=50;
double camXYAngle=0;
double camXZAngle=0;
int toggleCam = 0;
int camAngle = 60;
int lastX = 0;
int lastY = 0;
int buttonDown=0;

struct Config
{
    int arenaAltura;
    int arenaLargura;
    int jogadorRaioCabeca;
    int jogadorVelocidade;
    int inimigoRaioCabeca;
    int inimigoTirosPorSegundo;
    int inimigoVelocidadeTiro;
    int barrilAltura;
    int barrilLargura;
    int barrilNumeroTiros;
    int barrilnParaGanhar;
    int barrilVelocidade;
};

Config c;

Config carregarConfiguracoes()
{
    XMLDocument doc;
    doc.LoadFile("configuracoes.xml");
    XMLElement *arena = doc.FirstChildElement("jogo")->FirstChildElement("arena");
    XMLElement *jogador = doc.FirstChildElement("jogo")->FirstChildElement("jogador");
    XMLElement *inimigo = doc.FirstChildElement("jogo")->FirstChildElement("inimigo");
    XMLElement *barril = doc.FirstChildElement("jogo")->FirstChildElement("barril");

    Config c;
    c.arenaAltura = arena->IntAttribute("altura");
    c.arenaLargura = arena->IntAttribute("largura");
    c.jogadorRaioCabeca = jogador->IntAttribute("raioCabeca");
    c.jogadorVelocidade = jogador->IntAttribute("velocidade");
    c.inimigoRaioCabeca = inimigo->IntAttribute("raioCabeca");
    c.inimigoTirosPorSegundo = inimigo->IntAttribute("tirosPorSegungo");
    c.inimigoVelocidadeTiro = inimigo->IntAttribute("velocidadeTiro");
    c.barrilAltura = barril->IntAttribute("altura");
    c.barrilLargura = barril->IntAttribute("largura");
    c.barrilnParaGanhar = barril->IntAttribute("nParaGanhar");
    c.barrilNumeroTiros = barril->IntAttribute("numeroTiros");
    c.barrilVelocidade = barril->IntAttribute("velocidade");

    return c;
}

mesh gBarril;

struct Barril
{
public:
    int vida;
    bool temInimigo = false;
    Vector3f posicao;
    Vector3f velocidade;
    float angulo;
    float velocidadeAngular;
    float raioColisao;
    Vector3f miraInimigo;

    void Descer(float dt)
    {
        // Transladar na Superficia da Arena
        posicao += velocidade * dt;
        // Rotacionar
        angulo += velocidadeAngular * dt;
    }

    void atirar(float dt)
    {
    }
};

class jogador
{
    Vector3f posicao;
    float raioColisao;
    bool morreu;
    bool ganhou;
    int pontuacao;
    int movX;
    int movY;

    void mover(float dt)
    {
        if (movX == 0 && movY == 0)
        {
            return;
        }
    }
};

class game
{
    int tipoCamera = 1;
};

game *g;

/* TECLADO*/
void keyPress(unsigned char key, int x, int y){
/*
    keyStatus[(int)(key)] = 1;
    glutPostRedisplay();

*/
    switch (key){
        case '1': keyStatus[(int)('1')] = 1; break;
        case '2': keyStatus[(int)('2')] = 1; break;
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
void mouse(int button, int state, int x, int y) {}
void mouse_callback(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastX = x;
        lastY = y;
        buttonDown = 1;
    } 
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        buttonDown = 0;
    }
}
void mouse_motion(int x, int y){

    if (!buttonDown)
        return;
    
    camXYAngle += x - lastX;
    camXZAngle += y - lastY;
    
    camXYAngle = (int)camXYAngle % 360;
    camXZAngle = (int)camXZAngle % 360;
    
    lastX = x;
    lastY = y;
}
void passivemove(int x, int y) {}

void changeCamera(int angle, int w, int h){

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (angle, (GLfloat)w / (GLfloat)h, 1, 150.0);
    glMatrixMode (GL_MODELVIEW);
}
void reshape (int w, int h) {

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    changeCamera(camAngle, w, h);
}


void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glShadeModel (GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);

    ResetKeyStatus();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 15);

    gBarril.loadMesh("models/arena.obj");
    gBarril.loadTexture("models/textures.bmp");

    textureGround = LoadTextureRAW( "models/textures.bmp" );
    glEnable(GL_LIGHT0);
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

    if (keyStatus[(int)'1'] == 1){ 
        glTranslatef(0,0,-camDist);
        glRotatef(camXZAngle,1,0,0);
        glRotatef(camXYAngle,0,1,0);
    }
    else
        if (keyStatus[(int)'2'] == 1)
            gluLookAt( 5,10,5,  0,0,0,  0,0,1);
        else
            gluLookAt( 5,10,5,  0,0,0,  0,0,1);

    






    
   
    gBarril.draw();

    /* EIXOS = X-RED Y-GREEN Z-BLUE  */
    DrawAxes(3);
    DisplayPlane (textureGround, arenaLarg, arenaComp, 0);

    /* Desenhar no frame buffer! */
    glutSwapBuffers(); // Funcao apropriada para janela double buffer
}

int main(int argc, char *argv[])
{

    c = carregarConfiguracoes();

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
    glutSwapBuffers();
    glutMainLoop();

    return 0;
}

