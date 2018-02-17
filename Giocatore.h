#ifndef GIOCATORE_H
#define GIOCATORE_H

class Giocatore{
private:
  int x;
  int y;
  int velocita;
  int vite;

  bool andando_destra;
  bool andando_sinistra;
  bool saltando;
  bool sparando;


public:
  //salta
  ALLEGRO_BITMAP *salta;

	//sinistra
	ALLEGRO_BITMAP *verso_sinistra1;
	ALLEGRO_BITMAP *verso_sinistra2;
	ALLEGRO_BITMAP *verso_sinistra3;

	//destra
	ALLEGRO_BITMAP *verso_destra1;
	ALLEGRO_BITMAP *verso_destra2;
	ALLEGRO_BITMAP *verso_destra3;

  //spara
  ALLEGRO_BITMAP *sparando_verso_destra;
  ALLEGRO_BITMAP *spaando_verso_sinistra;

  Player();
  //sets
  void setX(int sx);
  void setY(int sy);
  void setVelocita(int v);
  void setVite(int v);
  void setAndando_destra(bool d);
  void setAndando_sinistra(bool s);
  void setSaltando(bool s);
  void setSparando(bool s);
  //get
  void getX();
  void getY();
  void getVelocita();
  void getVite();
  void getAndando_destra();
  void getAndando_sinistra();
  void getSaltando();
  void getSparando();

  void carica_immagini();



};

Player()
{
  x=170;
  y=128;
  speed=1;
  vite=3;

  salta= NULL;

	verso_sinistra1= NULL;
	verso_sinistra2= NULL;
	verso_sinistra3= NULL;

	verso_destra1= NULL;
	verso_destra2= NULL;
	verso_destra3= NULL;

  sparando_verso_destra= NULL;
  sparando_verso_sinistra= NULL;

}

void setX(int sx)
{
  x=sx;
}

void setY(int sy)
{
  y=sy;
}

void setVelocita(int v)
{
  velocita=v;
}
void setVite(int v)
{
  vite=v;
}

void setAndando_destra(bool d)
{
  andando_destra=d;
}
void setAndando_sinistra(bool s)
{
  andando_sinistra=s;
}
void setSaltando(bool s)
{
  saltando=s;
}
void setSparando(bool s)
{
  sparando=s;
}

int getX()
{
  return x;
}
int getY()
{
  return y;
}
int getVelocita()
{
  return velocita;
}
int getVite()
{
  return vite;
}
bool getAndando_destra()
{
  return andando_destra;
}
bool getAndando_sinistra()
{
  return andando_sinistra;
}
bool getSaltando()
{
  return saltando;
}
bool getSparando()
{
  return sparando;
}

void carica_immagini()
{
  salta= al_load_bitmap("./images/giocatore/salto.png");

	verso_sinistra1= al_load_bitmap("./images/giocatore/sinistra_1.png");
	verso_sinistra2= al_load_bitmap("./images/giocatore/sinistra_2.png");
	//verso_sinistra3= al_load_bitmap("./images/giocatore/");

	verso_destra1= al_load_bitmap("./images/giocatore/destra_1.png");
	verso_destra2= al_load_bitmap("./images/giocatore/destra_2.png");
	//verso_destra3= al_load_bitmap("./images/giocatore/");

  sparando_verso_destra=al_load_bitmap("./images/giocatore/sparo_dx1.png");
  sparando_verso_sinistra=al_load_bitmap("./images/giocatore/sparo_sx1.png");
}



#endif
