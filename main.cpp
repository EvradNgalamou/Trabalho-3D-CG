#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tinyxml2.h"
#include <ctime>

using namespace tinyxml2;

//Key status
int keyStatus[256];
float pe = 0.0;
float gX = 0;
float gY = 0;
float thetaArma = 0;
float gTempoDesdeUltimoSpawn = 0;

void tratamentoTiro();

struct Tiro
{
    float x;
    float y;
    bool visivel;
};
Tiro gTiros[100];

struct Barril
{
    bool temInimigo;
    float x;
    float y;
    int vida; // quando atinigir zero, o barril morre.
};
Barril gBarris[10];

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
    c.inimigoVelocidadeTiro = inimigo->IntAttribute("velocidade");
    c.barrilAltura = barril->IntAttribute("altura");
    c.barrilLargura = barril->IntAttribute("largura");
    c.barrilnParaGanhar = barril->IntAttribute("nParaGanhar");
    c.barrilNumeroTiros = barril->IntAttribute("numeroTiros");
    c.barrilVelocidade = barril->IntAttribute("velocidade");

    return c;
}

void keyPress(unsigned char key, int x, int y)
{
    keyStatus[(int) (key)] = 1;
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y)
{
    keyStatus[(int) (key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for (i = 0; i < 256; i++)
        keyStatus[i] = 0;
}

void mouse(int button, int state, int x, int y)
{
    if (state == 0)
    {
        tratamentoTiro();
    }
}

void movemouse(int x, int y)
{
    /*   y = c.arenaAltura -y;
       if (x<=0)
           x=1;
       if (x>=c.arenaLargura)
           x = c.arenaLargura; */
    if (x >= 0 && x <= c.arenaLargura)
    {
        if (x <= 0)
            x = 1;
        if (x <= c.arenaLargura / 2)
            thetaArma += (c.arenaLargura / x);
        else
            thetaArma -= (c.arenaLargura / x);
    }

    printf("x = %d\n", x);
    printf("y = %d\n\n", y);
}

void init()
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.

    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glOrtho(-(c.arenaLargura / 2),     // X coordinate of left edge
            (c.arenaLargura / 2),     // X coordinate of right edge
            0,     // Y coordinate of bottom edge
            c.arenaAltura,     // Y coordinate of top edge
            -100,     // Z coordinate of the “near” plane
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix
    glLoadIdentity();
}

void DesenharRect(float largura, float altura)
{
    /* Desenhar um polígono branco (retângulo) */
    glBegin(GL_POLYGON);
    {
        glVertex2f(0, 0);
        glVertex2f(largura, 0);
        glVertex2f(largura, altura);
        glVertex2f(0, altura);
    }
    glEnd();
}

void DesenharRectCentrado(float largura, float altura)
{
    // desenha um retangulo centrado na origem
    glPushMatrix();
    {
        glTranslated(-largura / 2, -altura / 2, 0);
        DesenharRect(largura, altura);
    }
    glPopMatrix();
}

void DesenharCirculo(float raio)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 361; i++)
    {
        glVertex2f(raio * cos(M_PI * i / 180), raio * sin(M_PI * i / 180));
    }
    glEnd();
}

void DesenharInimigo(int value)
{
    Barril *barril = &gBarris[value];

    if (barril->vida <= 0)
        return;

    glPushMatrix();
    {
        // x, y do barril é o centro do barril, para facilitar
        glTranslated(barril->x, barril->y, 0);

        //Desenhar Barril
        glPushMatrix();
        {
            glColor3f(1, 0.5, 0);
            DesenharRectCentrado(c.barrilAltura, c.barrilLargura);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glutPostRedisplay();
}

void DesenharJogador()
{
    glPushMatrix();
    {
        glTranslated(gX, gY + c.jogadorRaioCabeca + 30, 0);
        //proporcional a Cabeca do Jogador
        glScaled(c.jogadorRaioCabeca, c.jogadorRaioCabeca, 1);

        // Desenhar pe de frente
        glPushMatrix();
        {
            glColor3f(0, 0, 0);
            glTranslated(0.3, -0.5 + sin(pe), 0);
            DesenharRect(0.5, 1.3);
        }
        glPopMatrix();

        // Desenhar pe tras
        glPushMatrix();
        {
            glTranslated(-0.8, -0.5 - sin(pe), 0);
            DesenharRect(0.5, 1.3);
        }
        glPopMatrix();

        //Desenhar Arma
        glPushMatrix();
        {
            glRotated(thetaArma, 0, 0, 1);
            glColor3f(0.6, 0.1, 0);
            glTranslated(1, -0.8, 0);
            DesenharRect(0.5, 3);
        }
        glPopMatrix();

        // Desenhar Cabeca
        glColor3f(0, 0.7, 0);
        DesenharCirculo(1);

    }
    glPopMatrix();
}

void DesenharBala()
{

    //Transformação para o mundo da Arma
    glPushMatrix();
    {
        glColor3b(0, 0, 0);
        glTranslated(gX, gY + c.jogadorRaioCabeca + 30, 0);
        glScaled(c.jogadorRaioCabeca, c.jogadorRaioCabeca, 1);
        glRotated(thetaArma, 0, 0, 1);
        glTranslated(1, -0.8, 0);
        glTranslated(0.25, 3, 0);


        // Bala
        DesenharCirculo(0.2);
    }
    glPopMatrix();

}

void Desenha()
{
    DesenharJogador();
    for (int i = 0; i < 10; i++)
    {
        DesenharInimigo(i);
    }

    for (int i = 0; i < 100; i++)
    {
        if (gTiros[i].visivel)
        {
            DesenharBala();
        }
    }
}

void tratamentoTiro()
{
    for (int i = 0; i < 100; i++)
    {
        if (gTiros[i].visivel == false)
        {
            gTiros[i].visivel = true;
//           gTiros[i].x = posicaodoJogador
//           gTiros[i].y = posicaodoJogador
        }
    }
}

float gTempoDesdeUltimoIdle = 0;

void idle(void)
{
    // tempo desde o ultimo idle em segundos
    float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = 0.001f * (glutGet(GLUT_ELAPSED_TIME) - gTempoDesdeUltimoIdle);

    if (keyStatus[(int) ('w')])
    {
        if (gY > (c.arenaAltura / 2) - 2 * c.jogadorRaioCabeca)
        {
            gY = (c.arenaAltura / 2) - 2 * c.jogadorRaioCabeca;
            pe += 0.09;
        }
        else
        {
            gY += 1;
            pe += 0.09;
        }
    }

    if (keyStatus[(int) ('s')])
    {
        if (gY < -2)
            gY = -2;
        else
        {
            gY -= 1;
            pe += 0.09;
        }
    }

    if (keyStatus[(int) ('d')])
    {
        if (gX > (c.arenaLargura / 2) - c.jogadorRaioCabeca - 0.5 * c.jogadorRaioCabeca)
        {
            gX = (c.arenaLargura / 2) - c.jogadorRaioCabeca - (0.5 * c.jogadorRaioCabeca);
            pe += 0.09;
        }
        else
        {
            gX += 1;
            pe += 0.09;
        }
    }

    if (keyStatus[(int) ('a')])
    {
        if (gX < (-c.arenaLargura / 2) + c.jogadorRaioCabeca)
        {
            gX = (-c.arenaLargura / 2) + c.jogadorRaioCabeca;
            pe += 0.09;
        }
        else
        {
            gX -= 1;
            pe += 0.09;
        }
    }

    //tratamento de barris --------------------------------incompleto--------------------------------
    // movimenta barris beasedo no tempo dt
    for (int i = 0; i < 10; i++)
    {
        Barril *barril = &gBarris[i];
        if (barril->vida <= 0)
            continue;

        barril->y -= c.barrilVelocidade * dt;

        if (barril->y < -c.arenaAltura / 2)
        {
            barril->vida = 0;
            barril->temInimigo = false;
        }
    }

    // spawn de barris
    // 1% de chance de spawnar um barril
    float r = (float) rand() / RAND_MAX;
    float chance = 0.10f * dt; // 10% de chance por segundo
    // se tem nenhuma barril, aumenta a chance de spawnar
    for (int i = 0; i < 10; i++)
    {
        Barril *barril = &gBarris[i];
        if (barril->vida <= 0)
            chance += 0.05f * dt;
    }

    if (r < chance)
    {
        for (int i = 0; i < 10; i++)
        {
            Barril *barril = &gBarris[i];
            if (barril->vida > 0)
                continue;

            barril->vida = 300;
            // 20% de chance de spawnar um barril com inimigo
            barril->temInimigo = r < 0.2f * chance;
            barril->x = rand() % c.arenaLargura;
            if (barril->x < 0)
                barril->x = -barril->x;
            barril->x -= c.arenaLargura / 2;
            barril->y = c.arenaAltura - c.barrilAltura / 2;

            break;
        }
    }

    // Tratamento Tiro 
    for (int i = 0; i < 100; i++)
    {
//        tiro[i].y += velocidadeDeTiro * dt
//        if tiro esta forada tela
//            tiro.visivel = false
    }

    glutPostRedisplay();

    gTempoDesdeUltimoIdle = glutGet(GLUT_ELAPSED_TIME);
}

void display(void)
{
    /* Limpar todos os pixels  */
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f); // AZUL, no opacity(alpha).
    glClear(GL_COLOR_BUFFER_BIT);
    Desenha();

    /* Desenhar no frame buffer! */
    glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

int main(int argc, char *argv[])
{

    c = carregarConfiguracoes();

    // inicialização tiro e barris
    for (int j = 0; j < 100; j++)
    {
        gTiros[j].visivel = false;
        gTiros[j].x = 0;
        gTiros[j].y = 0;
    }

    for (int j = 0; j < 10; j++)
    {
        gBarris[j].temInimigo = false;
        gBarris[j].vida = 0;
        gBarris[j].x = 0;
        gBarris[j].y = 0;
    }

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
    glutMotionFunc(movemouse);
    glutIdleFunc(idle);
    init();
    glutSwapBuffers();
    glutMainLoop();

    return 0;
}