#include "Colpo.h"
#include "Giocatore.h"
Colpo::Colpo(){
  vita=false;
  raggio=0;
  spostamento=7;
  cambiaColore=false;
  colpo_destra=al_load_bitmap("./images/giocatore/sparo_dx1.png");
  colpo_destra2=al_load_bitmap("./images/giocatore/sparo_dx2.png");
  colpo_sinistra=al_load_bitmap("./images/giocatore/sparo_sx1.png");
  colpo_sinistra2=al_load_bitmap("./images/giocatore/sparo_sx2.png");

  x=0;
  y=0;
}

Colpo::~Colpo()
{
  al_destroy_bitmap(colpo_destra);
  al_destroy_bitmap(colpo_sinistra);
  al_destroy_bitmap(colpo_destra2);
  al_destroy_bitmap(colpo_sinistra2);




}

float Colpo::getX()
{
  return x;
}

float Colpo::getY()
{
  return y;
}

bool Colpo::getVita(){
  return vita;
}

void Colpo::setVita(bool s){
  vita=s;
}

void Colpo::drawColpo(){
  if(vita && direzione)
  {
    if(!cambiaColore)
    {
      al_draw_bitmap(colpo_destra, x, y, 0);
      cambiaColore=true;
    }
    else
    {
      al_draw_bitmap(colpo_destra2, x, y, 0);
      cambiaColore=false;
    }
  }
  else if(vita&& !direzione)
  {
    if(!cambiaColore)
    {
    al_draw_bitmap(colpo_sinistra, x, y, 0);
    cambiaColore=true;
  }
  else
  {
    al_draw_bitmap(colpo_sinistra2, x, y, 0);
    cambiaColore=false;
  }
  }
}


bool Colpo::fireColpo(float a, float b, bool d){

if(!vita)
direzione=d;
if(!vita && direzione)
{
 x=a+20;
 y=b+7;
 vita=true;
 return true;
}
else if(!vita && !direzione)
{
 x=a;
 y=b+7;
 vita=true;
 return true;
}

return false;
}

void Colpo::updateColpo()
{
  if(vita && direzione)
  {
    x+=spostamento;
    raggio+=spostamento;
    if(x>252 || raggio>=50)
       {
         vita=false;
         raggio=0;
       }
  }

  if(vita && !direzione)
  {
    x-=spostamento;
    raggio+=spostamento;
    if(x<0 || raggio>=50)
      {
        vita=false;
        raggio=0;
      }
  }
}
