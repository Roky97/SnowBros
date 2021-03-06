#ifndef COLPO_H
#define COLPO_H
#include "Giocatore.h"

class Colpo
{

private:
    float x;
    float y;
    bool vita;
    unsigned raggio;
    unsigned spostamento;
    bool direzione;
    bool cambiaColore;

public:
    Colpo();
    ~Colpo();
    Colpo(int,int,bool);

    float getX();
    float getY();
    bool getVita();
    void setVita(bool);

    void drawColpo();
    bool fireColpo(float,float,bool);
    void updateColpo();

    ALLEGRO_BITMAP *colpo_destra;
    ALLEGRO_BITMAP *colpo_destra2;

    ALLEGRO_BITMAP *colpo_sinistra;
    ALLEGRO_BITMAP *colpo_sinistra2;



};
#endif
