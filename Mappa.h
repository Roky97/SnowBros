#ifndef MAPPA_H
#define MAPPA_H
#include <fstream>
#include "Giocatore.h"
#include <string>
#include <algorithm>

class Mappa{
private:
  int loadcounterX;
  int loadcounterY;
  int mapsizeX;
  int mapsizeY;
  int map[12][11];
public:
  ALLEGRO_BITMAP *tile;
  ~Mappa();
  Mappa();
  void caricaElementi(const char* image);
  void caricaMappa (const char* nomefile);
  void drawMappa();
  int getValore(int, int);



};
#endif
