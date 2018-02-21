#include "Mostro.h"

Mostro::Mostro(int posx, int posy)
{
  x=posx;
  y=posy;
  velocita=1;


	verso_sinistra1= NULL;
	verso_sinistra2= NULL;
	verso_sinistra3= NULL;

	verso_destra1= NULL;
	verso_destra2= NULL;
	verso_destra3= NULL;
}

void Mostro::setX(int sx)
{
  x=sx;
}

void Mostro::setY(int sy)
{
  y=sy;
}

void Mostro::setVelocita(int v)
{
  velocita=v;
}


void Mostro::setAndando_destra(bool d)
{
  andando_destra=d;
}
void Mostro::setAndando_sinistra(bool s)
{
  andando_sinistra=s;
}

int Mostro::getX()
{
  return x;
}
int Mostro::getY()
{
  return y;
}
int Mostro::getVelocita()
{
  return velocita;
}

bool Mostro::getAndando_destra()
{
  return andando_destra;
}
bool Mostro::getAndando_sinistra()
{
  return andando_sinistra;
}
