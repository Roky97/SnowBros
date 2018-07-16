#ifndef MOSTRO_ROSSO
#define MOSTRO_ROSSO
#include "Mostro.h"

class Mostro_rosso : public Mostro
{

public:

    Mostro_rosso();
    Mostro_rosso(float, float);
    ~Mostro_rosso();

    void setSaltando(bool);

    void carica_immagini();
    void drawMostro();
    void muovi();



};
#endif
