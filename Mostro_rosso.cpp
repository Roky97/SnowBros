#include "Mostro_rosso.h"

Mostro_rosso::Mostro_rosso()
{
  Mostro();
  saltando =false;
  andando_destra=true;
  andando_sinistra=false;
  colpito=false;
  nColpito=0;
}

Mostro_rosso::Mostro_rosso(float x1, float y2)
{
  Mostro(x1,y2);
  saltando=false;
  andando_destra=true;
  andando_sinistra=false;
  colpito=false;
  nColpito=0;

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

  salta = al_load_bitmap("./images/mostro_rosso/salto.png");
}

void Mostro_rosso::drawMostro(){

  if(andando_destra && !colpito && !passo)
    {
      al_draw_scaled_bitmap(verso_destra1, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
      cont++;

      if(cont==7)
       {
         passo=true;
         cont=0;
       }
    }

  else if(andando_destra && !colpito && passo)
    {
        al_draw_scaled_bitmap(verso_destra2, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
        cont++;

      if(cont==7)
      {
        passo=false;
        cont=0;
      }
    }

  if(andando_sinistra && !colpito && !passo)
  {
    al_draw_scaled_bitmap(verso_sinistra1, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }
  }
  else if(andando_sinistra && !colpito && passo)
  {
   al_draw_scaled_bitmap(verso_sinistra2, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
    cont++;

    if(cont==7)
    {
      passo=false;
      cont=0;
    }
  }

  if(saltando || cadendo)
  {
    al_draw_scaled_bitmap(salta, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
  }

}

void Mostro_rosso::muovi(){


/*if(x+spostamento>=1105 && andando_destra)
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
}*/

if(andando_destra && !colpito && x+42<1105) //movimento a dx aggiorna la x che corrisponde alla larghezza schermo
{
  x+=spostamento;
}
else if(andando_destra && !colpito && x+42>=1105)
{
  andando_destra=false;
  andando_sinistra=true;
}

else if(andando_sinistra && !colpito && x>=78) //movimento a sx
  x-=spostamento;
  else if(andando_sinistra && !colpito && x<78)
  {
    andando_destra=true;
    andando_sinistra=false;
  }

}

void Mostro_rosso::collisioneProiettile(int a, int b)
{
  a+=14;
  b+=22;
  if(a <= static_cast<int>(x) && a + 10 >= static_cast<int>(x) && b >= y && b <= (y+44))
  {
    colpito=true;
    nColpito++;
    setAndando_destra(false);
    setAndando_sinistra(false);
  }
}
