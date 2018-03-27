#include "Mostro.h"

Mostro::Mostro(){
  spostamento=7;
  x=0;
  y=0;
    andando_sinistra=false;
  	verso_sinistra1= NULL;
  	verso_sinistra2= NULL;

  	verso_destra1= NULL;
  	verso_destra2= NULL;
    passo=false;
    cont=0;

}
Mostro::Mostro(float posx, float posy)
{
  x=posx;
  y=posy;
  spostamento=7;


  andando_sinistra=false;
  passo=false;
  cont=0;
	verso_sinistra1= NULL;
	verso_sinistra2= NULL;
	//verso_sinistra3= NULL;

	verso_destra1= NULL;
	verso_destra2= NULL;
	//verso_destra3= NULL;
}

//SETS

void Mostro::setX(float sx)
{
  x=sx;
}

void Mostro::setY(float sy)
{
  y=sy;
}

void Mostro::setVita(bool v){
  vita=v;
}


void Mostro::setAndando_destra(bool d)
{
  andando_destra=d;
}
void Mostro::setAndando_sinistra(bool s)
{
  andando_sinistra=s;
}



//GETS
float Mostro::getX()
{
  return x;
}
float Mostro::getY()
{
  return y;
}

bool Mostro::getAndando_destra()
{
  return andando_destra;
}
bool Mostro::getAndando_sinistra()
{
  return andando_sinistra;
}

bool Mostro::getVita(){
  return vita;
}
