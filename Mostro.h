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
private:
  int x;
  int y;
  int velocita;

  bool andando_destra;
  bool andando_sinistra;


public:
	//sinistra
	ALLEGRO_BITMAP *verso_sinistra1;
	ALLEGRO_BITMAP *verso_sinistra2;
	//ALLEGRO_BITMAP *verso_sinistra3;

	//destra
	ALLEGRO_BITMAP *verso_destra1;
	ALLEGRO_BITMAP *verso_destra2;
	//ALLEGRO_BITMAP *verso_destra3;


  Mostro(int, int);
  //sets
  void setX(int sx);
  void setY(int sy);
  void setVelocita(int v);

  void setAndando_destra(bool d);
  void setAndando_sinistra(bool s);

  //get
  int getX();
  int getY();
  int getVelocita();

  bool getAndando_destra();
  bool getAndando_sinistra();


  virtual void carica_immagini()=0;



};
#endif
