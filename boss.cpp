#include "boss.h"

Boss::Boss()
{
  x=800;
  y=500;

  vita=true;
  nColpito=0;

  timerSalta=al_create_timer(1.0);
  sputaFuoco=al_create_timer(1.0);
  caduta=al_create_timer(1.0/10);

  saltoDistanza=0;

  fermo1=al_load_bitmap("./images/boss/fermo1.png");
  fermo2=al_load_bitmap("./images/boss/fermo2.png");
  salta=al_load_bitmap("./images/boss/salta.png");
  sconfitto1=al_load_bitmap("./images/boss/sconfitto1.png");
  sconfitto2=al_load_bitmap("./images/boss/sconditto2.png");

  fuoco1 = al_load_bitmap("./images/mostro_verde/fuoco1_dx.png");
  fuoco2 = al_load_bitmap("./images/mostro_verde/fuoco2_dx.png");

  srand(time(0));
}
Boss::~Boss()
{
al_destroy_timer(timerSalta);
al_destroy_timer(timerSalta);
al_destroy_timer(timerSalta);

al_destroy_bitmap(fermo1);
al_destroy_bitmap(fermo2);
al_destroy_bitmap(salta);
al_destroy_bitmap(sconfitto1);
al_destroy_bitmap(sconfitto2);

}

void Boss::setX(float x1)
{
  x=x1;
}

void Boss::setY (float x2)
{
  y=y1;
}

void Boss::setSaltando(bool s)
{
  saltando=s;
}

void setCadendo(bool s);
{
  cadendo=s;
}

float Boss::getX()
{
  return x;
}

float Boss::getY()
{
  return y;
}

int Boss::getnColpito();
{
  return nColpito;
}

bool Boss::getVita()
{
  return vita;
}

bool Boss::getSaltando()
{
  return saltando();
}

int Boss::getxFuoco()
{
  return xFuoco;
}

int Boss::getyFuoco()
{
  return yFuoco;
}

bool getCadendo()
{
  return cadendo;
}


void Boss::gravita()
{
    y+=parametroGravita;
}

void drawBoss()
{
  if(al_get_timer_started(caduta))
  {
    if(al_get_timer_count(caduta)==0)
      al_draw_scaled_bitmap(sconfitto1, 0, 0, 59, 43, x-78, y-50, 59*6, 43*6, 0);
    else if(al_get_timer_count(caduta)>=1)
      al_draw_scaled_bitmap(sconfitto2, 0, 0, 59, 43, x-78, y-50, 59*6, 43*6, 0);
  }
  else
  {
    if((saltando || cadendo) && !sparaFuoco)
      al_draw_scaled_bitmap(salta, 0, 0, 47, 63, x-78, y-50, 47*5.2, 63*6, 0);
    else if(passo)// (passo|| sparafuoco)
      {
        al_draw_scaled_bitmap(fermo1, 0, 0, 47, 63, xFuoco, yFuoco, 47*6, 63*6, 0);
        cont++;

        if(cont==7)
        {
          passo=false;
          cont=0;
        }
      }
      else if(!passo)
      {
        al_draw_scaled_bitmap(fermo2, 0, 0, 47, 63, xFuoco, yFuoco, 47*6, 63*6, 0);
        cont++;

        if(cont==7)
        {
          passo=true;
          cont=0;
        }
      }
      if(sparaFuoco)
      {
        //al_draw_scaled_bitmap(sputa_fuoco_dx, 0, 0, 20, 17, x-78, y, 20*6, 17*6, 0);
        if(passo)
        {
          al_draw_scaled_bitmap(fuoco1_dx, 0, 0, 19, 10, xFuoco, yFuoco, 19*10, 10*10, 0);
          cont++;

          if(cont==7)
  
            passo=false;
            cont=0;
          }
        }
        else
        {
          al_draw_scaled_bitmap(fuoco2_dx, 0, 0, 19, 10, xFuoco, yFuoco, 19*10, 10*10, 0);
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

void Boss::gestisciBoss()
{
  if(!al_get_timer_started(timerSalta)
  {
    al_start_timer(timerSalta);
  }

  if(!al_get_timer_started(sputaFuoco)
  {
    al_start_timer(sputaFuoco);
  }

  if(al_get_timer_count(sputaFuoco==3))
  {
    sparaFuoco=true;
  }

  if(al_get_timer_count(timerSalta)==4)
  {
    saltando=true;
  }

  if(nColpito==30)
  {
    vita=false;
    al_start_timer(caduta);
  }

  if(saltando)
  {
    salta();
  }

  if(sparaFuoco)
  {
    xFuoco-=10;
    lunghezzaFuoco-=10;
    if(lunghezzaFuoco<=0)
    {
      sparaFuoco=false;
      xFuoco=-100;
      yFuoco=-100;
      lunghezzaFuoco=1000;
      al_set_timer_count(sputaFuoco,0.0);
    }
  }
}

void Boss::salta()
{
  if(saltando && saltoDistanza<=225 && !cadendo) //aggiorna le posizioni per saltare
  {
    y-=15;
    saltoDistanza+=15;
    if(saltoDistanza>=500)
    {
      saltando=false;
      saltoDistanza=0;
      al_set_timer_count(timerSalta, 0.0);
      cadendo=true;
    }
  }
}

bool Boss::controllaSeToccato(int a, int b, int tipo)
{
  if((a+40>=x && a-40<=x) && b+70 >=y && b-70 <= y)) //sistemare l'intervallo
  {
    if(tipo==0)
      nColpito++;
    else
      nColpito+=5;
    return true;
  }
  return false;
}

bool Boss::getSparaFuoco()
{
  return sparaFuoco;
}
