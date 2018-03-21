#ifndef GIOCATORE_H
#define GIOCATORE_H
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

class Giocatore{
private:

  unsigned w;
  unsigned h;

  unsigned x;
  unsigned y;
  unsigned velocita;
  unsigned vite;
  unsigned spostamento;

  bool fermo;
  bool andando_destra;
  bool andando_sinistra;
  bool saltando;
  bool sparando;
  bool potere_v;


public:
  //salta
  ALLEGRO_BITMAP *salta;

  //fermo
  ALLEGRO_BITMAP *fermo_destra;
  ALLEGRO_BITMAP *fermo_sinistra;

	//sinistra
	ALLEGRO_BITMAP *verso_sinistra1;
	ALLEGRO_BITMAP *verso_sinistra2;
	//ALLEGRO_BITMAP *verso_sinistra3;

	//destra
	ALLEGRO_BITMAP *verso_destra1;
	ALLEGRO_BITMAP *verso_destra2;
	//ALLEGRO_BITMAP *verso_destra3;

  //spara
  ALLEGRO_BITMAP *sparando_verso_destra;
  ALLEGRO_BITMAP *sparando_verso_sinistra;

  Giocatore(int, int);

  //sets
  void setX(unsigned sx);
  void setY(unsigned sy);
  void setVelocita(unsigned v);
  void setVite(unsigned v);
  void setAndando_destra(bool d);
  void setAndando_sinistra(bool s);
  void setSaltando(bool s);
  void setSparando(bool s);

  //get
  unsigned getX();
  unsigned getY();
  unsigned & getVelocita();
  unsigned & getVite();
  bool getAndando_destra();
  bool getAndando_sinistra();
  bool getSaltando();
  bool getSparando();

  //Immagini e disegno
  void carica_immagini();
  void drawPersonaggio();

  //Movimenti
  void muovi();
  
};
#endif
