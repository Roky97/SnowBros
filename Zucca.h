#ifndef ZUCCA_H
#define ZUCCA_H
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
#include <iostream>
using namespace std;

class Zucca
{
private:
  float x;
  float y;
  float spostamento;
  int cont;
  bool vita;
  bool changeBitmap;
  bool andando_destra;
  bool andando_sinistra;
  ALLEGRO_BITMAP *dx1;
  ALLEGRO_BITMAP *dx2;

  ALLEGRO_BITMAP *sx1;
  ALLEGRO_BITMAP *sx2;



public:
  Zucca();
  Zucca(float ,float );
  ~Zucca();

  void drawZucca();
  void muoviZucca(float,float);

  void setVita(bool );
  void setX(float );
  void setY(float );

  bool getVita();
  float getX();
  float getY();


};
#endif
