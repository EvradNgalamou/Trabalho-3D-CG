#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tinyxml2.h"
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

struct vetor3f{
    float x;
    float y;
    float z;
};


class Barril {
    int vida;
    bool temInimigo = false;
    vetor3f posicao;
    vetor3f velocidade;
    float angulo;
    float velocidadeAngular;
    float raioColisao;
    vetor3f miraInimigo;

    void Descer( float dt){
        // Transladar na Superficia da Arena
        posicao.x += velocidade.x * dt;
        posicao.y += velocidade.y * dt;
        posicao.z += velocidade.z * dt;
        // Rotacionar 
        angulo += velocidadeAngular *dt;
    }

    void atirar (float dt){

    }


};

class jogador {
    vetor3f posicao;
    float raioColisao;
    bool morreu;
    bool ganhou;
    int pontuacao;
    int movX;
    int movY;

    void mover(float dt){
        if (movX == 0 && movY == 0){
            return ;
        }
    }



};


class game{
    int tipoCamera = 1;



};

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

void mouse(int button, int state, int x, int y){}

void passivemove(int x, int y){}

void init()
{
    ResetKeyStatus();
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

void display(game* g)
{
    /* Limpar todos os pixels  */
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f); // AZUL, no opacity(alpha).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
     



    /* Desenhar no frame buffer! */
    glutSwapBuffers(); // Funcao apropriada para janela double buffer
}

int main(int argc, char *argv[])
{

    c = carregarConfiguracoes();

    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

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