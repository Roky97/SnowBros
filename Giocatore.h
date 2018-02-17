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
  bool salta;

public:
  //jump
  ALLEGRO_BITMAP *jump;

	//LEFT
	ALLEGRO_BITMAP *verso_sinistra1;
	ALLEGRO_BITMAP *verso_sinistra2;
	ALLEGRO_BITMAP *verso_sinistra3;
	//RIGHT
	ALLEGRO_BITMAP *verso_destra1;
	ALLEGRO_BITMAP *verso_destra2;
	ALLEGRO_BITMAP *verso_destra3;

  Player();
  //sets
  void setX(int x);
  void setY(int y);
  void setVelocita(int v);
  void setVite(int v);
  void setAndando_destra(bool d);
  void setAndando_sinistra(bool s);
  void setSalta(bool s);




};
#endif
