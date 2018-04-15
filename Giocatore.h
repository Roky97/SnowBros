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

  float x;
  float y;
  unsigned velocita;
  unsigned vite;
  unsigned spostamento;
  unsigned cont;
  unsigned parametroGravita;
  unsigned saltoDistanza;
  unsigned colpoDistanza;
  unsigned cont1;

  bool fermo;
  bool fermoAlternato;
  bool andando_destra;
  bool andando_sinistra;
  bool andando_sotto;
  bool andando_sopra;

  bool saltando;
  bool sparando;
  bool potere_v;
  bool passo;
  bool cadendo;
  bool toccato;
  bool spostaMostro;
  ALLEGRO_TIMER *trasformazione;

public:
  //salta
  ALLEGRO_BITMAP *salta;

  //fermo
  ALLEGRO_BITMAP *fermo_destra;
  ALLEGRO_BITMAP *fermo_sinistra;

	//sinistra
	ALLEGRO_BITMAP *verso_sinistra1;
	ALLEGRO_BITMAP *verso_sinistra2;
  ALLEGRO_BITMAP *lancia_sinistra1;
  ALLEGRO_BITMAP *lancia_sinistra2;
  ALLEGRO_BITMAP *sposta_verso_sinistra1;
  ALLEGRO_BITMAP *sposta_verso_sinistra2;




	//destra
	ALLEGRO_BITMAP *verso_destra1;
	ALLEGRO_BITMAP *verso_destra2;
  ALLEGRO_BITMAP *lancia_destra1;
  ALLEGRO_BITMAP *lancia_destra2;
  ALLEGRO_BITMAP *sposta_verso_destra1;
  ALLEGRO_BITMAP *sposta_verso_destra2;


  ALLEGRO_BITMAP *toccato1;
  ALLEGRO_BITMAP *toccato2;
  ALLEGRO_BITMAP *toccato3;

  ALLEGRO_BITMAP *lanterna;

ALLEGRO_BITMAP *trasformazione1dx;
ALLEGRO_BITMAP *trasformazione2dx;
ALLEGRO_BITMAP *trasformazione3dx;
ALLEGRO_BITMAP *trasformazione1sx;
ALLEGRO_BITMAP *trasformazione2sx;
ALLEGRO_BITMAP *trasformazione3sx;

ALLEGRO_BITMAP *grande_fermo1;
ALLEGRO_BITMAP *grande_fermo2;
ALLEGRO_BITMAP *grande_destra1;
ALLEGRO_BITMAP *grande_destra2;
ALLEGRO_BITMAP *grande_sinistra1;
ALLEGRO_BITMAP *grande_sinistra2;









  Giocatore(int, int);
  ~Giocatore();

  //sets
  void setX(unsigned sx);
  void setY(unsigned sy);
  void setVelocita(unsigned v);
  void setVite(unsigned v);
  void setAndando_destra(bool d);
  void setAndando_sinistra(bool s);
  void setAndando_sopra(bool s);
  void setAndando_sotto(bool s);
  void setSaltando(bool s);
  void setSparando(bool s);
  void setFermo(bool s);
  void setPasso(bool s);
  void setCadendo(bool s);
  void setToccato(bool s);
  void setSpostaMostro(bool s);
  void setCont1(unsigned c);
  void setPotere(bool p);


  //get
  float getX();
  float getY();
  unsigned getVelocita();
  unsigned getVite();
  bool getAndando_destra();
  bool getAndando_sinistra();
  bool getAndando_sopra();
  bool getAndando_sotto();
  bool getSaltando();
  bool getSparando();
  bool getCadendo();
  bool getFermoalternato();
  bool getToccato();
  int getCont();
  bool getSpostaMostro();
  unsigned getSpostamento();
  unsigned getCont1();
  bool getPotere();



  //Immagini e disegno
  void carica_immagini();
  void drawPersonaggio();
  void drawLanterna(float ,float);

  //Movimenti
  void muovi();
  void gravita();
  bool controllaTocco(int a, int b, bool i,bool c);
  void controllaseToccato(int a,int b);
  bool controllaseToccatoSushi(int a, int b);
  void presaLanterna(int a,int b);
  void disattivaPotere();

};
#endif
