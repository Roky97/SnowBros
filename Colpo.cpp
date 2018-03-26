#include "Colpo.h"
#include "Giocatore.h"
Colpo::Colpo(){
  vita=false;
  raggio=0;
  spostamento=10;
  colpo_destra=al_load_bitmap("./images/giocatore/sparo_dx1.png");
  colpo_sinistra=al_load_bitmap("./images/giocatore/sparo_sx1.png");
}

void Colpo::drawColpo(){
  if(vita && direzione)
  {
    al_draw_scaled_bitmap(colpo_destra, 0, 0, 7, 11, x, y, 7*4, 11*4, 0);
  }
  else if(vita&& !direzione)
  {
    al_draw_scaled_bitmap(colpo_sinistra, 0, 0, 7, 11, x, y, 7*4, 11*4, 0);
  }
}


bool Colpo::fireColpo(float a, float b, bool d){

if(!vita)
direzione=d;
if(!vita && direzione)
{
 x=a+20;
 y=b;
 vita=true;
 return true;
}
else if(!vita && !direzione)
{
 x=a-20;
 y=b;
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
    if(x>1105 || raggio>=200)
       {
         vita=false;
         raggio=0;
       }
  }

  if(vita && !direzione)
  {
    x-=spostamento;
    raggio+=spostamento;
    if(x<0 || raggio>=200)
      {
        vita=false;
        raggio=0;
      }
  }
}
