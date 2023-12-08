#include "Config.h"
#include "tinyxml2.h"

using namespace tinyxml2;

void Config::load(Config* config) {
    XMLDocument doc;
    int err = doc.LoadFile("configuracoes.xml");

    if (err != 0) {
        printf("Erro ao carregar arquivo de configuracoes\n");
        exit(1);
    }

    XMLElement* jogo = doc.FirstChildElement("jogo");

    XMLElement* arena = jogo->FirstChildElement("arena");
    XMLElement* jogador = jogo->FirstChildElement("jogador");
    XMLElement* inimigo = jogo->FirstChildElement("inimigo");
    XMLElement* barril = jogo->FirstChildElement("barril");

    config->arenaAltura = arena->IntAttribute("altura");
    config->arenaLargura = arena->IntAttribute("largura");
    config->jogadorRaioCabeca = jogador->IntAttribute("raioCabeca");
    config->jogadorVelocidade = jogador->IntAttribute("velocidade");
    config->inimigoRaioCabeca = inimigo->IntAttribute("raioCabeca");
    config->inimigoTirosPorSegundo = inimigo->IntAttribute("tirosPorSegungo");
    config->inimigoVelocidadeTiro = inimigo->IntAttribute("velocidadeTiro");
    config->barrilAltura = barril->IntAttribute("altura");
    config->barrilLargura = barril->IntAttribute("largura");
    config->barrilnParaGanhar = barril->IntAttribute("nParaGanhar");
    config->barrilNumeroTiros = barril->IntAttribute("numeroTiros");
    config->barrilVelocidade = barril->IntAttribute("velocidade");
}
