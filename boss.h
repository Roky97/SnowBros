#define BOSS_H
#ifndef BOSS_H

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

class Boss{
private:
  float x;
  float y;
  int nColpito;
  bool vita;
  bool passo;

  bool cadendo;

  bool saltando;
  int saltoDistanza;

  int xFuoco, yFuoco;
  bool sparaFuoco;
  int lunghezzaFuoco;


  ALLEGRO_TIMER *timerSalta;
  ALLEGRO_TIMER *sputaFuoco;
  ALLEGRO_TIMER *caduta;






public:

  ALLEGRO_BITMAP * fermo1;
  ALLEGRO_BITMAP * fermo2;
  ALLEGRO_BITMAP * salta;
  ALLEGRO_BITMAP * sconfitto1;
  ALLEGRO_BITMAP * sconfitto2;
  ALLEGRO_BITMAP * fuoco1_dx
  ALLEGRO_BITMAP * fuoco2_dx


  Boss();
  ~Boss();

  void setX(float);
  void setY(float);
  void setnColpito(float);
  void setSaltando(float);
  void setCadendo(float);

  float getY();
  int getnColpito();
  bool getVita();
  bool getSaltando();
  int getxFuoco();
  int getyFuoco();
  bool getSparaFuoco();
  bool getCadendo();

  void gestisciBoss();
  void salta();
  void gravita();
  bool controllaSeToccato(int, int, int);
  void drawBoss();





};
#endif
