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

void keyPress(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 1;
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    // Initialize keyStatus
    for (i = 0; i < 256; i++)
        keyStatus[i] = 0;
}

void mouse(int button, int state, int x, int y) {}


float prev_alpha = 0;
float prev_beta = 0;

int prev_x = 0;
int prev_y = 0;

float radius = 15;
float radian60 = 60 * M_PI / 180.0;

void passivemove(int x, int y) {
    int dx = x - prev_x;
    int dy = y - prev_y;

    float da = 0.007 * dx;
    float db = 0.02 * dy;

    float alpha = prev_alpha + da;
    float beta = prev_beta + db;

    if (beta < -radian60) {
        beta = -radian60;
    } else if (beta > radian60) {
        beta = radian60;
    }

    prev_alpha = alpha;
    prev_beta = beta;

    prev_x = x;
    prev_y = y;
}

void init()
{
    ResetKeyStatus();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 50);

    gBarril.loadMesh("models/arena.obj");
    gBarril.loadTexture("models/textures.bmp");
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

void display()
{
    /* Limpar todos os pixels  */
    //  glClearColor(0.0f, 0.5f, 0.8f, 1.0f); // AZUL, no opacity(alpha).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        radius * cos(-prev_alpha) * cos(prev_beta),
        radius * sin(-prev_alpha) * cos(prev_beta),
        6+radius * sin(prev_beta),
        0, 0, 6,
        0, 0, 1
    );

    glPushMatrix();
    // Desenhar arena
    glColor3f(0, 0, 1); // Azul.
    glRotatef(5, 1, 0, 0);
    glTranslatef(0, 0, -0.05);
    glScaled(10, 10, 0.1);
    glutWireCube(1);
    glPopMatrix();

    DesenhaJogador();
   
    glClear(GL_DEPTH_BUFFER_BIT);

    glScaled(4, 4, 4);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();

    /* EIXOS = X-RED Y-GREEN Z-BLUE  */
    DrawAxes(3);

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
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passivemove);
    glutIdleFunc(idle);
    init();
    glutSwapBuffers();
    glutMainLoop();

    return 0;
}