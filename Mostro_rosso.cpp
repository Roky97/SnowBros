#include "Mostro_rosso.h"

Mostro_rosso::Mostro_rosso(float x, float y)
{
  Mostro(x,y);
  saltando=false;
}

bool Mostro_rosso::getSaltando()
{
  return saltando;
}

void Mostro_rosso::setSaltando(bool s)
{
  saltando=s;
}

 void Mostro_rosso::carica_immagini()
{
  verso_sinistra1=al_load_bitmap("./images/mostro_rosso/sinistra_1.png");
  verso_sinistra2=al_load_bitmap("./images/mostro_rosso/sinistra_2.png");

  verso_destra1=al_load_bitmap("./images/mostro_rosso/destra_1.png");
  verso_destra2=al_load_bitmap("./images/mostro_rosso/destra_2.png");
}

void Mostro_rosso::drawMostro(){

  if(andando_destra && !passo)
    {
      al_draw_scaled_bitmap(verso_destra1, 0, 0, 20, 12, x, y, 20*4, 12*4, 0);
      cont++;

      if(cont==7)
       {
         passo=true;
         cont=0;
       }
    }

  else if(andando_destra && passo)
    {
        al_draw_scaled_bitmap(verso_destra2, 0, 0, 20, 17, x, y, 20*4, 17*4, 0);
        cont++;

      if(cont==7)
      {
        passo=false;
        cont=0;
      }
    }

  if(andando_sinistra && !passo)
  {
    al_draw_scaled_bitmap(verso_sinistra1, 0, 0, 20, 17, x, y, 20*4, 17*4, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }
  }
  else if(andando_sinistra && passo)
  {
   al_draw_scaled_bitmap(verso_sinistra2, 0, 0, 20, 17, x, y, 20*4, 17*4, 0);
    cont++;

    if(cont==7)
    {
      passo=false;
      cont=0;
    }
  }

}

void Mostro_rosso::muovi(){


if(x+spostamento>=1105 && andando_destra)
{
  andando_destra=false;
  andando_sinistra=true;
}
else if(andando_destra)
{
  x+=spostamento;
}

if(x-spostamento<=0 && andando_sinistra)
{
  andando_sinistra=false;
  andando_destra=true;
}
else if(andando_sinistra)
{
  x-=spostamento;
}

}
