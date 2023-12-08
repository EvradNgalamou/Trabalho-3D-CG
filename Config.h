#ifndef CONFIG_H
#define CONFIG_H


struct Config {
    int arenaAltura;
    int arenaLargura;
    float jogadorRaioCabeca;
    int jogadorVelocidade;
    int inimigoRaioCabeca;
    int inimigoTirosPorSegundo;
    int inimigoVelocidadeTiro;
    int barrilAltura;
    int barrilLargura;
    int barrilNumeroTiros;
    int barrilnParaGanhar;
    int barrilVelocidade;

    static void load(Config* config);
};


#endif //CONFIG_H
