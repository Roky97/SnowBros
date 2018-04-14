#include "Mostro_Verde.h"

Mostro_Verde::Mostro_Verde()
{
  Mostro();
  saltando =false;
  // andando_destra=true;
  // andando_sinistra=false;
  colpito=false;
  nColpito=0;
  al_start_timer(congelo);
  contPrimaDiSparare=200;
  sparaFuoco=false;
  lunghezzaFuoco=300;
  xFuoco=0;
  yFuoco=0;
  tipo=1;

}

Mostro_Verde::~Mostro_Verde()
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

void Mostro_Verde::setSparaFuoco(bool l)
{
  sparaFuoco=l;
}

bool Mostro_Verde::getSparaFuoco()
{
  return sparaFuoco;
}

Mostro_Verde::Mostro_Verde(float x1, float y2)
{
  Mostro(x1,y2);
  saltando=false;
  andando_destra=true;
  andando_sinistra=false;
  colpito=false;
  nColpito=0;
  tipo=1;
  sparaFuoco=false;

}


 void Mostro_Verde::carica_immagini()
{
  verso_sinistra1=al_load_bitmap("./images/mostro_verde/sinistra1.png");
  verso_sinistra2=al_load_bitmap("./images/mostro_verde/sinistra2.png");
  colpito_sinistra1=al_load_bitmap("./images/mostro_verde/colpito1_sx.png");
  colpito_sinistra2=al_load_bitmap("./images/mostro_verde/colpito2_sx.png");

  verso_destra1=al_load_bitmap("./images/mostro_verde/destra1.png");
  verso_destra2=al_load_bitmap("./images/mostro_verde/destra2.png");
  colpito_destra1=al_load_bitmap("./images/mostro_verde/colpito1_dx.png");
  colpito_destra2=al_load_bitmap("./images/mostro_verde/colpito2_dx.png");

  salta = al_load_bitmap("./images/mostro_verde/salto.png");
  sputa_fuoco_dx = al_load_bitmap("./images/mostro_verde/sputa_fuoco_dx.png");
  sputa_fuoco_sx = al_load_bitmap("./images/mostro_verde/sputa_fuoco_sx.png");
  fuoco1_dx = al_load_bitmap("./images/mostro_verde/fuoco1_dx.png");
  fuoco2_dx = al_load_bitmap("./images/mostro_verde/fuoco2_dx.png");
  fuoco1_sx = al_load_bitmap("./images/mostro_verde/fuoco1_sx.png");
  fuoco2_sx = al_load_bitmap("./images/mostro_verde/fuoco2_sx.png");
}

void Mostro_Verde::drawMostro(){

if(vita==false)
  {
    drawSushi();
  }
else
{

if(!colpitoInnevato)
{
  if((saltando || cadendo) && !sparaFuoco)
  {
    al_draw_scaled_bitmap(salta, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
  }
 else if(andando_destra && !colpito && !passo && !sparaFuoco)
    {
      al_draw_scaled_bitmap(verso_destra1, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
      cont++;

      if(cont==7)
       {
         passo=true;
         cont=0;
       }
    }

  else if(andando_destra && !colpito && passo && !sparaFuoco)
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

  else if(andando_sinistra && !colpito && !passo && !sparaFuoco)
  {
    al_draw_scaled_bitmap(verso_sinistra1, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }
  }
  else if(andando_sinistra && !colpito && passo && !sparaFuoco)
  {
   al_draw_scaled_bitmap(verso_sinistra2, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
    cont++;

    if(cont==7)
    {
      passo=false;
      cont=0;
    }
  }
  if(andando_sinistra && colpito && !passo)
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

    if(sparaFuoco && nColpito==0)
    {
      if(fuocoDir)
      {
        al_draw_scaled_bitmap(sputa_fuoco_dx, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
        if(passo)
        {
          al_draw_scaled_bitmap(fuoco1_dx, 0, 0, 19, 10, xFuoco, yFuoco, 19*6, 10*6, 0);
          cont++;

          if(cont==7)
          {
            passo=false;
            cont=0;
          }
        }
        else
        {
          al_draw_scaled_bitmap(fuoco2_dx, 0, 0, 19, 10, xFuoco, yFuoco, 19*6, 10*6, 0);
          cont++;

          if(cont==7)
          {
            passo=true;
            cont=0;
          }
        }
      }
      else if(!fuocoDir)
      {
        al_draw_scaled_bitmap(sputa_fuoco_sx, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
        if(passo)
        {
          al_draw_scaled_bitmap(fuoco1_sx, 0, 0, 19, 10, xFuoco, yFuoco, 19*6, 10*6, 0);
          cont++;

          if(cont==7)
          {
            passo=false;
            cont=0;
          }
        }
        else
        {
          al_draw_scaled_bitmap(fuoco2_sx, 0, 0, 19, 10, xFuoco, yFuoco, 19*6, 10*6, 0);
          cont++;

          if(cont==7)
          {
            passo=true;
            cont=0;
          }
        }

      }
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
}

void Mostro_Verde::muovi(){
if(colpitoInnevato)
{
  //al_stop_timer(congelo);
  colpitoEdInnevato();
}
else
{
  if(sparaFuoco)
  {
    if(fuocoDir)
    {
      xFuoco+=10;
      lunghezzaFuoco-=10;
      if(lunghezzaFuoco<=0)
      {
        sparaFuoco=false;
        xFuoco=-100;
        yFuoco=-100;
        lunghezzaFuoco=300;
        srand(time(0));
        contPrimaDiSparare=rand()%300+ 500;

      }

    }
    else if(!fuocoDir)
    {
      xFuoco-=10;
      lunghezzaFuoco-=10;
      if(lunghezzaFuoco<=0)
      {
        sparaFuoco=false;
        xFuoco=-100;
        yFuoco=-100;
        lunghezzaFuoco=300;
        srand(time(0));
        contPrimaDiSparare=rand()%300+ 500;
      }
    }
  }
  else
  {
if(andando_destra && !colpito && x+42<1105) //movimento a dx aggiorna la x che corrisponde alla larghezza schermo
{
  x+=spostamento;
  contPrimaDiSparare-=spostamento;
  if(contPrimaDiSparare<=0 && !saltando && !cadendo && nColpito==0)
  {
    fuocoDir=true;
    sparaFuoco=true;
    xFuoco=x;
    yFuoco=y;
    srand((unsigned)time(NULL));
    contPrimaDiSparare=rand()%300+ 500;
  }
}
else if(andando_destra && !colpito && x+42>=1105)
{
  andando_destra=false;
  andando_sinistra=true;
  diminuisciContPrimaDiSaltare();
}

else if(andando_sinistra && !colpito && x>=78)
{//movimento a sx
  x-=spostamento;
  contPrimaDiSparare-=spostamento;
  if(contPrimaDiSparare<=0 && !saltando && !cadendo && nColpito==0)
  {
    fuocoDir=false;
    sparaFuoco=true;
    xFuoco=x-200;
    yFuoco=y;
    srand((unsigned)time(NULL));
    contPrimaDiSparare=rand()%300+ 500;
  }
}
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
      contPrimaDiSaltare=rand()%7;
      cadendo=true;
    }
  }


}

}

}
