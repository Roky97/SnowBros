#include "Giocatore.h"
Giocatore::Giocatore()
{
  x=170;
  y=128;
  velocita=1;
  vite=3;
  
  potere_v=false;
  andando_destra=false;
  andando_sinistra=false;
  saltando=false;
  sparando=false;


  salta= NULL;

	verso_sinistra1= NULL;
	verso_sinistra2= NULL;
	//verso_sinistra3= NULL;

	verso_destra1= NULL;
	verso_destra2= NULL;
	//verso_destra3= NULL;

  sparando_verso_destra= NULL;
  sparando_verso_sinistra= NULL;

}

void Giocatore::setX(unsigned sx)
{
  x=sx;
}

void Giocatore::setY(unsigned sy)
{
  y=sy;
}

void Giocatore::setVelocita(unsigned v)
{
  velocita=v;
}
void Giocatore::setVite(unsigned v)
{
  vite=v;
}

void Giocatore::setAndando_destra(bool d)
{
  andando_destra=d;
}
void Giocatore::setAndando_sinistra(bool s)
{
  andando_sinistra=s;
}
void Giocatore::setSaltando(bool s)
{
  saltando=s;
}
void Giocatore::setSparando(bool s)
{
  sparando=s;
}

unsigned Giocatore::getX()
{
  return x;
}
unsigned Giocatore::getY()
{
  return y;
}
unsigned & Giocatore::getVelocita()
{
  return velocita;
}
unsigned & Giocatore::getVite()
{
  return vite;
}
bool Giocatore::getAndando_destra()
{
  return andando_destra;
}
bool Giocatore::getAndando_sinistra()
{
  return andando_sinistra;
}
bool Giocatore::getSaltando()
{
  return saltando;
}
bool Giocatore::getSparando()
{
  return sparando;
}

void Giocatore::carica_immagini()
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

void Giocatore::diminiusci_vita()
{
  vite--;
}
void Giocatore::potere_verde()
{
  if(potere_v)
  {
    velocita*=3;
  }
}
