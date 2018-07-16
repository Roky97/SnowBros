#ifndef MOSTRO_H
#define MOSTRO_H
#include <cstdlib>
#include <ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
using namespace std;

class Mostro
{
protected:
    float x;
    float y;
    float spostamento;
    int cont;
    int tipo;
    int xFuoco, yFuoco;
    int iSushi;
    unsigned parametroGravita;
    unsigned nColpito;
    unsigned saltoDistanza;
    unsigned contPrimaDiSaltare;
    ALLEGRO_TIMER *congelo;


    bool andando_destra;
    bool andando_sinistra;
    bool vita;
    bool passo;
    bool cadendo;
    bool saltando;
    bool colpito;
    bool totInnevato;
    bool colpitoInnevato;
    bool sushi;




public:
    ALLEGRO_BITMAP *verso_sinistra1;
    ALLEGRO_BITMAP *verso_sinistra2;
    ALLEGRO_BITMAP *colpito_sinistra1;
    ALLEGRO_BITMAP *colpito_sinistra2;


    ALLEGRO_BITMAP *verso_destra1;
    ALLEGRO_BITMAP *verso_destra2;
    ALLEGRO_BITMAP *colpito_destra1;
    ALLEGRO_BITMAP *colpito_destra2;

    ALLEGRO_BITMAP *innevando1;
    ALLEGRO_BITMAP *innevando2;
    ALLEGRO_BITMAP *innevando3;
    ALLEGRO_BITMAP *palladineve1;
    ALLEGRO_BITMAP *palladineve2;

    ALLEGRO_BITMAP *salta;

    ALLEGRO_BITMAP *im_sushi[5];


    Mostro();
    ~Mostro();
    Mostro(float, float);

    void setX(float sx);
    void setY(float sy);

    void setAndando_destra(bool d);
    void setAndando_sinistra(bool s);
    void setVita(bool v);
    void setCadendo(bool c);
    void setSaltando(bool s);
    void setColpito(bool c);
    void setContPrimaDiSaltare(unsigned c);
    void setTotInnevato(bool i);
    void setcolpitoInnevato(bool i);
    void setnColpito(unsigned c);
    void setSushi(bool s);

    float getX();
    float getY();
    bool getVita();

    bool getAndando_destra();
    bool getAndando_sinistra();
    bool getSaltando();
    bool getCadendo();
    bool getColpito();
    unsigned getContPrimaDiSaltare();
    bool getTotInnevato();
    unsigned getnColpito();
    bool getcolpitoInnevato();
    int getTipo();
    int getxFuoco();
    int getyFuoco();
    bool getSushi();
    int getIndiceSushi();



    virtual void carica_immagini() {}
    virtual void drawMostro() {}
    virtual void muovi() {}
    bool collisioneProiettile(int, int, bool);

    bool controllaSeToccato(int, int, bool, bool);
    void diminuisciContPrimaDiSaltare();
    void muoviDaTommySeInnevato(bool, bool, unsigned);
    void drawSushi();
    void colpitoEdInnevato();
    void sconfitto();

    void gravita();

};
#endif
