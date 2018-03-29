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
  colpito_sinistra1=al_load_bitmap("./images/mostro_rosso/colpito_sx1.png");
  colpito_sinistra2=al_load_bitmap("./images/mostro_rosso/colpito_sx2.png");

  verso_destra1=al_load_bitmap("./images/mostro_rosso/destra_1.png");
  verso_destra2=al_load_bitmap("./images/mostro_rosso/destra_2.png");
  colpito_destra1=al_load_bitmap("./images/mostro_rosso/colpito_dx1.png");
  colpito_destra2=al_load_bitmap("./images/mostro_rosso/colpito_dx2.png");

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
    else if(andando_destra && colpito && !passo)
    {
      al_draw_scaled_bitmap(colpito_destra1, 0, 0, 20, 17, x-78, y-25, 20*6, 17*6, 0);
      cont++;

    if(cont==7)
    {
      passo=true;
      cont=0;
    }
    }
    else if(andando_destra && colpito && passo)
    {
      al_draw_scaled_bitmap(colpito_destra2, 0, 0, 20, 17, x-78, y-25, 20*6, 17*6, 0);
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
  else if(andando_sinistra && colpito && !passo)
  {
    al_draw_scaled_bitmap(colpito_sinistra1, 0, 0, 20, 17, x-78, y-25, 20*6, 17*6, 0);
    cont++;

  if(cont==7)
  {
    passo=true;
    cont=0;
  }
  }
  else if(andando_sinistra && colpito && passo)
  {
    al_draw_scaled_bitmap(colpito_sinistra2, 0, 0, 20, 17, x-78, y-25, 20*6, 17*6, 0);
    cont++;

  if(cont==7)
  {
    passo=false;
    cont=0;
  }
  }

  if(colpito && nColpito>=1 && nColpito<3)
  {
    al_draw_scaled_bitmap(innevando1, 0, 0, 26, 30, x-78, y-50, 26*5.2, 30*5.2, 0);
  }
  else if(colpito && nColpito>=3 && nColpito<5)
    {
      al_draw_scaled_bitmap(innevando2, 0, 0, 26, 30, x-78, y-50, 26*5.2, 30*5.2, 0);

    }
    else if(colpito && nColpito>=5 && nColpito<7)
    {
      al_draw_scaled_bitmap(innevando3, 0, 0, 26, 30, x-78, y-50, 26*5.2, 30*5.2, 0);

    }
    else if(colpito && nColpito>=7)
    {
      al_draw_scaled_bitmap(palladineve1, 0, 0, 25, 31, x-78, y-50, 25*5.2, 31*5.2, 0);

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
//cout<<al_get_timer_count(congelo)<<endl;
  if(colpito && al_get_timer_count(congelo)%3==0)
  {
    cout<<al_get_timer_count(congelo)<<endl;
    cout<<nColpito<<endl<<endl;
    nColpito-=1;
    if(nColpito==0)
    {
      colpito=false;
      //al_stop_timer(congelo);
    }
  }

}

void Mostro_rosso::collisioneProiettile(int a, int b)
{
  a+=14;
  b+=22;
  if(a <= static_cast<int>(x) && a + 10 >= static_cast<int>(x) && b >= y && b <= (y+44))
  {
     if(colpito==false)
      al_start_timer(congelo);
    colpito=true;
    nColpito++;
  }
}
