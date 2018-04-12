#ifndef MOSTRO_VERDE
#define MOSTRO_VERDE
#include "Mostro.h"

class Mostro_Verde : public Mostro{
private:
  bool sparaFuoco;
  int contPrimaDiSparare;
  int lunghezzaFuoco;
  int xFuoco, yFuoco;
  bool fuocoDir;

public:

  ALLEGRO_BITMAP *sputa_fuoco_dx;
  ALLEGRO_BITMAP *sputa_fuoco_sx;
  ALLEGRO_BITMAP *fuoco1_dx;
  ALLEGRO_BITMAP *fuoco2_dx;
  ALLEGRO_BITMAP *fuoco1_sx;
  ALLEGRO_BITMAP *fuoco2_sx;




  Mostro_Verde();
  Mostro_Verde(float, float);
  ~Mostro_Verde();

  void setSaltando(bool);
  void setSparaFuoco(bool);

  bool getSparaFuoco();

  void carica_immagini();
  void drawMostro();
  void muovi();
  // bool collisioneProiettile(int, int,bool);
  // bool controllaSeToccato(int, int, bool, bool);



};
#endif
