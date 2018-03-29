#ifndef MOSTRO_ROSSO
#define MOSTRO_ROSSO
#include "Mostro.h"

class Mostro_rosso : public Mostro{
private:
  bool saltando;

public:

  Mostro_rosso();
  Mostro_rosso(float, float);

  bool getSaltando();
  void setSaltando(bool);

  void carica_immagini();
  void drawMostro();
  void muovi();
  bool collisioneProiettile(int, int);


};
#endif
