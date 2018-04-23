#ifndef MAPPA_H
#define MAPPA_H
#include <fstream>
#include "Giocatore.h"
#include <string>
#include <algorithm>
#include "Mostro.h"

class Mappa{
private:
  int loadcounterX;
  int loadcounterY;
  int mapsizeX;
  int mapsizeY;
  int map[15][15];
public:
  ALLEGRO_BITMAP *tile;
  ~Mappa();
  Mappa();
  void caricaElementi(const char* image);
  void caricaMappa (const char* nomefile);
  void drawMappa();
  int getValore(int, int);
  int getMapSizeX();
  int getMapSizeY();



};
#endif
