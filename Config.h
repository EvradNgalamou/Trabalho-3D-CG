#ifndef CONFIG_H
#define CONFIG_H


struct Config {
    float arenaAltura;
    float arenaLargura;
    float jogadorRaioCabeca;
    float jogadorVelocidade;
    float inimigoRaioCabeca;
    int inimigoTirosPorSegundo;
    float inimigoVelocidadeTiro;
    float barrilAltura;
    float barrilLargura;
    int barrilNumeroTiros;
    int barrilnParaGanhar;
    float barrilVelocidade;

    static void load(Config* config);
};


#endif //CONFIG_H
