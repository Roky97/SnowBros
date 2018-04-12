#include "Mostro_rosso.h"

Mostro_rosso::Mostro_rosso()
{
  Mostro();
  saltando =false;
  // andando_destra=true;
  // andando_sinistra=false;
  colpito=false;
  nColpito=0;
  al_start_timer(congelo);

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
Mostro_rosso::~Mostro_rosso()
{
al_destroy_bitmap(innevando1);
al_destroy_bitmap(innevando2);
al_destroy_bitmap(innevando3);
al_destroy_bitmap(palladineve1);
al_destroy_bitmap(palladineve2);

al_destroy_bitmap(verso_sinistra1);
al_destroy_bitmap(verso_sinistra2);
al_destroy_bitmap(colpito_sinistra1);
al_destroy_bitmap(colpito_sinistra2);
al_destroy_bitmap(verso_destra1);
al_destroy_bitmap(verso_destra2);
al_destroy_bitmap(colpito_destra1);
al_destroy_bitmap(colpito_destra2);
al_destroy_bitmap(salta);



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

if(!colpitoInnevato)
{
  if(saltando || cadendo)
  {
    al_draw_scaled_bitmap(salta, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
  }
 else if(andando_destra && !colpito && !passo)
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

  else if(andando_sinistra && !colpito && !passo)
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
  }

  else         //PALLA DI NEVE CHE ROTOLA
  {
    if(!passo)
    {
      al_draw_scaled_bitmap(palladineve1, 0, 0, 25, 31, x-78, y-50, 25*5.2, 31*5.2, 0);
      cont++;
      if(cont==7)
       {
         passo=true;
         cont=0;
       }
    }
    if(passo)
    {
      al_draw_scaled_bitmap(palladineve2, 0, 0, 25, 31, x-78, y-50, 25*5.2, 31*5.2, 0);
      cont++;
      if(cont==7)
       {
         passo=false;
         cont=0;
       }
    }
  }
}

void Mostro_rosso::muovi(){

if(colpitoInnevato)
{
  //al_stop_timer(congelo);
  parametroGravita=20;
  if(andando_destra)
  {
    if(x+42>=1105)
      {
        vita=false;
        totInnevato=false;
        colpito=false;
        nColpito=0;
        colpitoInnevato=false;
      } //qua caso mai facciamo una animazione
    x+=spostamento+20;
  }
  else if(andando_sinistra)
  {
    if(x<50)
      {
        vita=false;
        totInnevato=false;
        colpito=false;
        nColpito=0;
        colpitoInnevato=false;
      }
    x-=spostamento+20;
  }
}
else
{
if(andando_destra && !colpito && x+42<1105) //movimento a dx aggiorna la x che corrisponde alla larghezza schermo
{
  x+=spostamento;
}
else if(andando_destra && !colpito && x+42>=1105)
{
  andando_destra=false;
  andando_sinistra=true;
  diminuisciContPrimaDiSaltare();
}

else if(andando_sinistra && !colpito && x>=78) //movimento a sx
  x-=spostamento;
else if(andando_sinistra && !colpito && x<78)
  {
    andando_destra=true;
    andando_sinistra=false;
    diminuisciContPrimaDiSaltare();
  }

if(colpito && al_get_timer_count(congelo)%25==0 )
  {
    nColpito-=1;
    if(nColpito==0)
    {
      colpito=false;
      //al_stop_timer(congelo);
    }
    if(nColpito<7)
    {
      totInnevato=false;
    }
  }

  if(saltando && saltoDistanza<=225 && !cadendo) //aggiorna le posizioni per saltare
  {
    y-=15;
    saltoDistanza+=15;
    if(saltoDistanza>=225)
    {
      saltando=false;
      saltoDistanza=0;
      contPrimaDiSaltare=rand()%4;
      cadendo=true;
    }
  }
}

}
