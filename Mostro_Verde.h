#ifndef MOSTRO_VERDE
#define MOSTRO_VERDE
#include "Mostro.h"

class Mostro_Verde : public Mostro{
private:
  bool lanciaFuoco;
  int contFuoco;

public:

  Mostro_Verde();
  Mostro_Verde(float, float);
  ~Mostro_Verde();

  void setSaltando(bool);
  void setLanciaFuoco(bool);

  bool getLanciaFuoco();

  void carica_immagini();
  void drawMostro();
  void muovi();
  // bool collisioneProiettile(int, int,bool);
  // bool controllaSeToccato(int, int, bool, bool);



};
#endif
