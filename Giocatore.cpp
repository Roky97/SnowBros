#include "Giocatore.h"
Giocatore::Giocatore(int w, int h)
{
  this->w=w;
  this->h=h;
  // x=w/2.0 - 15;
  // y=h-30*4 -21*(4);
  x=w/2.0 - 15;
  y=0;
  spostamento=7;
  vite=3;
  cont=0;
  parametroGravita=10;
  saltoDistanza=0;
  colpoDistanza=0;

  fermo=true;
  fermoAlternato=false;
  potere_v=false;
  andando_destra=false;
  andando_sinistra=false;
  saltando=false;
  sparando=false;
  passo=false;
  cadendo=false;

  salta= NULL;

	verso_sinistra1= NULL;
	verso_sinistra2= NULL;
  lancia_sinistra1=NULL;
  lancia_sinistra2=NULL;

	verso_destra1= NULL;
	verso_destra2= NULL;
  lancia_destra1=NULL;
  lancia_destra2=NULL;

  colpo_destra=NULL;
  colpo_sinistra=NULL;

}

//SETS
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

void Giocatore::setFermo(bool s)
{
  fermo=s;
}

void Giocatore::setPasso(bool s)
{
  passo=s;
}

//GETS
float Giocatore::getX()
{
  return x;
}

float Giocatore::getY()
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

bool Giocatore::getCadendo()
{
  return cadendo;
}

bool Giocatore::getFermoalternato(){
return fermoAlternato;
}

void Giocatore::setCadendo(bool s)
{
  cadendo=s;
}

//IMMAGINI E DISEGNO

void Giocatore::carica_immagini()
{
  salta= al_load_bitmap("./images/giocatore/salto.png");

  fermo_destra=al_load_bitmap("./images/giocatore/fermo_dx.png");
  fermo_sinistra=al_load_bitmap("./images/giocatore/fermo_sx.png");

	verso_sinistra1= al_load_bitmap("./images/giocatore/sinistra_1.png");
	verso_sinistra2= al_load_bitmap("./images/giocatore/sinstra_2.png");
	//verso_sinistra3= al_load_bitmap("./images/giocatore/");

	verso_destra1= al_load_bitmap("./images/giocatore/destra_dx1.png");
	verso_destra2= al_load_bitmap("./images/giocatore/destra_2.png");
	//verso_destra3= al_load_bitmap("./images/giocatore/");

  colpo_destra=al_load_bitmap("./images/giocatore/sparo_dx1.png");
  colpo_sinistra=al_load_bitmap("./images/giocatore/sparo_sx1.png");

  lancia_sinistra1=al_load_bitmap("./images/giocatore/lancia_sx2.png");
  lancia_sinistra2=al_load_bitmap("./images/giocatore/lancia_sx3.png");
  lancia_destra1=al_load_bitmap("./images/giocatore/lancia_dx2.png");
  lancia_destra2=al_load_bitmap("./images/giocatore/lancia_dx3.png");

  colpo_destra=al_load_bitmap("./images/giocatore/sparo_dx1.png");
  colpo_sinistra=al_load_bitmap("./images/giocatore/sparo_sx1.png");
}

void Giocatore::drawPersonaggio()
{
  if(fermo && fermoAlternato && !andando_destra && !andando_sinistra && !cadendo)
  {
    if(sparando && passo)
      al_draw_scaled_bitmap(lancia_destra1, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    else if(sparando && !passo)
    al_draw_scaled_bitmap(lancia_destra2, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);

    else
      al_draw_scaled_bitmap(fermo_destra, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    cont++;

    if(cont==7)
     {
       if(passo)
        passo=false;
        else
        passo=true;
       cont=0;
     }
  }

  else if(fermo && !fermoAlternato && !andando_destra && !andando_sinistra && !cadendo)
  {
    if(sparando && passo)
      al_draw_scaled_bitmap(lancia_sinistra1, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    if(sparando & !passo)
    al_draw_scaled_bitmap(lancia_sinistra2, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);

    else
      al_draw_scaled_bitmap(fermo_sinistra, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);

    cont++;

    if(cont==7)
     {
       if(passo)
        passo=false;
        else
        passo=true;
       cont=0;
     }
  }

  else if(saltando && !andando_destra && !andando_sinistra && !cadendo)
  {
    if(sparando)
      al_draw_scaled_bitmap(lancia_destra1, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    else
    al_draw_scaled_bitmap(salta, 0, 0, 24, 32, x-60, y-27, 24*4, 32*4, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }

  }

   if(cadendo)
   {
    if(sparando)
      al_draw_scaled_bitmap(lancia_destra1, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    else
      al_draw_scaled_bitmap(salta, 0, 0, 24, 32, x-60, y-27, 24*4, 32*4, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }
   }

  else if(andando_destra && !passo)
    {
      if(sparando)
        al_draw_scaled_bitmap(lancia_destra1, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
      else
        al_draw_scaled_bitmap(verso_destra1, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
      cont++;

      if(cont==7)
       {
         passo=true;
         cont=0;
       }
       fermoAlternato=true;
    }

  else if(andando_destra && passo)
    {
      if(sparando)
        al_draw_scaled_bitmap(lancia_destra2, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
      else
        al_draw_scaled_bitmap(verso_destra2, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
      cont++;

      if(cont==7)
      {
        passo=false;
        cont=0;
      }
      fermoAlternato=true;
    }

  else if(andando_sinistra && !passo)
  {
    if(sparando)
      al_draw_scaled_bitmap(lancia_sinistra1, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    else
      al_draw_scaled_bitmap(verso_sinistra1, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }
     fermoAlternato=false;
  }

  else if(andando_sinistra && passo)
  {
    if(sparando)
      al_draw_scaled_bitmap(lancia_sinistra2, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    else
      al_draw_scaled_bitmap(verso_sinistra2, 0, 0, 30, 30, x-60, y-25, 30*4, 30*4, 0);
    cont++;

    if(cont==7)
    {
      passo=false;
      cont=0;
    }

    fermoAlternato=false;
  }
}

//MOVIMENTI

void Giocatore::muovi()
{
  if(andando_destra && x<=w-30-spostamento) //movimento a dx aggiorna la x che corrisponde alla larghezza schermo
  {
    x+=spostamento;
  }

  else if(andando_sinistra && x>-25) //movimento a sx
    x-=spostamento;

  if(saltando && saltoDistanza<=210 && !cadendo) //aggiorna le posizioni per saltare
  {
    y-=15;
    saltoDistanza+=15;
    if(saltoDistanza>=210)
    {
      saltando=false;
      fermo=false;
      saltoDistanza=0;
      cadendo=true;
    }
  }
}

void Giocatore::spara(float a){

if(andando_destra || fermoAlternato)
  {
    for(int i=7; i<=210 ;i+=7)
    {
      al_draw_scaled_bitmap(colpo_destra, 0, 0, 30, 30, a+i, y-25, 30*4, 30*4, 0);
    }
  }
//if(andando_sinistra || !fermoAlternato)
}

void Giocatore::gravita()
{
  y+=parametroGravita;

}
