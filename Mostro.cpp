#include "Mostro.h"

Mostro::Mostro(){
  spostamento=5;
  x=0;
  y=0;
    andando_sinistra=false;
    andando_destra=true;

  	verso_sinistra1= NULL;
  	verso_sinistra2= NULL;
    colpito_sinistra1=NULL;
    colpito_sinistra2=NULL;

  	verso_destra1= NULL;
  	verso_destra2= NULL;
    colpito_destra1=NULL;
    colpito_destra2=NULL;

    innevando1=al_load_bitmap("./images/neve/innevando1.png");
    innevando2=al_load_bitmap("./images/neve/innevando2.png");
    innevando3=al_load_bitmap("./images/neve/innevando3.png");
    palladineve1=al_load_bitmap("./images/neve/palladineve1.png");
    palladineve2=al_load_bitmap("./images/neve/palladineve2.png");

    congelo=al_create_timer(1.0/5);

    salta=NULL;

    passo=false;
    cont=0;
    parametroGravita=10;

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

	verso_destra1= NULL;
	verso_destra2= NULL;
}

Mostro::~Mostro()
{
  al_destroy_bitmap(innevando1);
  al_destroy_bitmap(innevando2);
  al_destroy_bitmap(innevando3);
  al_destroy_bitmap(palladineve1);
  al_destroy_bitmap(palladineve2);


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

void Mostro::setSaltando(bool s)
{
  saltando=s;
}

void Mostro::setCadendo(bool c)
{
  cadendo=c;
}

void Mostro::setColpito(bool c)
{
  colpito=c;
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

bool Mostro::getSaltando()
{
    return saltando;
}
bool Mostro::getCadendo()
{
  return cadendo;
}

bool Mostro::getColpito()
{
  return colpito;
}


void Mostro::gravita()
{
    y+=parametroGravita;
}
