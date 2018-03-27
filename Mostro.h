#ifndef MOSTRO_H
#define MOSTRO_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Mostro{
protected:
  float x;
  float y;
  int spostamento;
  int cont;

  bool andando_destra;
  bool andando_sinistra;
  bool vita;
  bool passo;


public:
	//sinistra
	ALLEGRO_BITMAP *verso_sinistra1;
	ALLEGRO_BITMAP *verso_sinistra2;
	//ALLEGRO_BITMAP *verso_sinistra3;

	//destra
	ALLEGRO_BITMAP *verso_destra1;
	ALLEGRO_BITMAP *verso_destra2;
	//ALLEGRO_BITMAP *verso_destra3;


  Mostro();
  Mostro(float, float);
  //sets
  void setX(float sx);
  void setY(float sy);

  void setAndando_destra(bool d);
  void setAndando_sinistra(bool s);
  void setVita(bool v);

  //get
  float getX();
  float getY();
  bool getVita();

  bool getAndando_destra();
  bool getAndando_sinistra();


  virtual void carica_immagini(){}
  virtual void drawMostro(){}
  virtual void muovi(){}

};
#endif
