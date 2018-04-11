#ifndef MOSTRO_VERDE
#define MOSTRO_VERDE
#include "Mostro.h"

class Mostro_Verde : public Mostro{

public:

  Mostro_Verde();
  Mostro_Verde(float, float);

  void setSaltando(bool);

  void carica_immagini();
  void drawMostro();
  void muovi();
  bool collisioneProiettile(int, int,bool);
  bool controllaSeToccato(int, int, bool, bool);



};
#endif
