#ifndef COLPO_H
#define COLPO_H
#include "Giocatore.h"


class Colpo{

private:
  float x;
  float y;
  bool vita;
  unsigned raggio;
  unsigned spostamento;
  bool direzione;

public:
  Colpo();
  Colpo(int,int,bool);
  void drawColpo();
  bool fireColpo(float,float,bool);
  void updateColpo();
  //colpo
  ALLEGRO_BITMAP *colpo_destra;
  ALLEGRO_BITMAP *colpo_sinistra;


};
#endif