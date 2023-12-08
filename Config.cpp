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

    config->arenaAltura = arena->FloatAttribute("altura");
    config->arenaLargura = arena->FloatAttribute("largura");
    config->jogadorRaioCabeca = jogador->FloatAttribute("raioCabeca");
    config->jogadorVelocidade = jogador->FloatAttribute("velocidade");
    config->inimigoRaioCabeca = inimigo->FloatAttribute("raioCabeca");
    config->inimigoTirosPorSegundo = inimigo->FloatAttribute("tirosPorSegungo");
    config->inimigoVelocidadeTiro = inimigo->FloatAttribute("velocidadeTiro");
    config->barrilAltura = barril->FloatAttribute("altura");
    config->barrilLargura = barril->FloatAttribute("largura");
    config->barrilnParaGanhar = barril->FloatAttribute("nParaGanhar");
    config->barrilNumeroTiros = barril->FloatAttribute("numeroTiros");
    config->barrilVelocidade = barril->FloatAttribute("velocidade");
}
