#include "Colpo.h"

Colpo::Colpo(){
  vita=false;
  raggio=200;
  spostamento=10;
}

void Colpo::drawColpo(){
  if(vita && direzione)
  {
    al_draw_scaled_bitmap(colpo_destra, 0, 0, 7, 11, x, y, 7*4, 11*4, 0);
  }

  if(vita&& !direzione)
  {
    al_draw_scaled_bitmap(colpo_sinistra, 0, 0, 7, 11, x, y, 7*4, 11*4, 0);
  }
}


void Colpo::fireColpo(float a, float b, bool d){

direzione=d;
if(!vita && d)
{
 x=a+20;
 y=b;
 vita=true;
}
else if(!vita && !d)
{
 x=a-20;
 y=b;
 vita=true;
}

}

void Colpo::updateColpo(){}
