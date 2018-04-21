#include "Boss.h"

Boss::Boss()
{
  x=170;
  y=100;

  vita=true;
  nColpito=0;
  parametroGravita=10;
  cont=0;
  lunghezzaFuoco=250;

  timerSalta=al_create_timer(1.0);
  sputaFuoco=al_create_timer(1.0);
  caduta=al_create_timer(1.0/10);

  saltoDistanza=0;

  fermo1=al_load_bitmap("./images/boss/fermo1.png");
  fermo2=al_load_bitmap("./images/boss/fermo2.png");
  salta=al_load_bitmap("./images/boss/salta.png");
  sconfitto1=al_load_bitmap("./images/boss/sconfitto1.png");
  sconfitto2=al_load_bitmap("./images/boss/sconfitto2.png");

  fuoco1 = al_load_bitmap("./images/mostro_verde/fuoco1_sx.png");
  fuoco2 = al_load_bitmap("./images/mostro_verde/fuoco2_sx.png");
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

void Boss::setY (float y1)
{
  y=y1;
}

void Boss::setSaltando(bool s)
{
  saltando=s;
}

void Boss::setCadendo(bool s)
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

int Boss::getnColpito()

{
  return nColpito;
}

bool Boss::getVita()
{
  return vita;
}

bool Boss::getSaltando()
{
  return saltando;
}

int Boss::getxFuoco()
{
  return xFuoco;
}

int Boss::getyFuoco()
{
  return yFuoco;
}

bool Boss::getCadendo()
{
  return cadendo;
}

bool Boss::getSparaFuoco()
{
  return sparaFuoco;
}

void Boss::gravita()
{
    y+=parametroGravita;
}

void Boss::drawBoss()
{
  if(al_get_timer_started(caduta))
  {
    if(al_get_timer_count(caduta)>=0 && al_get_timer_count(caduta)<=3)
      al_draw_scaled_bitmap(sconfitto1,  0, 0, al_get_bitmap_width(sconfitto1),  al_get_bitmap_height(sconfitto1), x-10, y+20, al_get_bitmap_width(sconfitto1)*1.5, al_get_bitmap_height(sconfitto1)*1.5, 0);

    else if(al_get_timer_count(caduta)>=4)
      al_draw_scaled_bitmap(sconfitto2,  0, 0, al_get_bitmap_width(sconfitto2),  al_get_bitmap_height(sconfitto2), x-40, y+30, al_get_bitmap_width(sconfitto2)*1.5, al_get_bitmap_height(sconfitto2)*1.5, 0);
  }
  else
  {
    if(sparaFuoco)
    {
      //al_draw_bitmap(sputa_fuoco_dx,  x-78, y, 0);
      if(passo)
      {
        al_draw_scaled_bitmap(fuoco1,  0, 0, al_get_bitmap_width(fuoco1),  al_get_bitmap_height(fuoco1), xFuoco, yFuoco, al_get_bitmap_width(fuoco1)*2, al_get_bitmap_height(fuoco1)*2, 0);
        cont++;

        if(cont==7)
        {
          passo=false;
          cont=0;
        }
      }
      else if(!passo)
      {
        al_draw_scaled_bitmap(fuoco2,  0, 0, al_get_bitmap_width(fuoco2),  al_get_bitmap_height(fuoco2), xFuoco, yFuoco, al_get_bitmap_width(fuoco2)*2, al_get_bitmap_height(fuoco2)*2, 0);
        cont++;

        if(cont==7)
        {
          passo=true;
          cont=0;
        }
      }
    }
    if((saltando || cadendo) && !sparaFuoco)
        al_draw_scaled_bitmap(salta,  0, 0, al_get_bitmap_width(salta),  al_get_bitmap_height(salta), x, y, al_get_bitmap_width(salta)*1.5, al_get_bitmap_height(salta)*1.5, 0);
    else
    {
      if(passo)// (passo|| sparafuoco)
      {
                al_draw_scaled_bitmap(fermo1,  0, 0, al_get_bitmap_width(fermo1),  al_get_bitmap_height(fermo1), x, y, al_get_bitmap_width(fermo1)*1.5, al_get_bitmap_height(fermo1)*1.5, 0);
        cont++;

        if(cont==15)
        {
          passo=false;
          cont=0;
        }
      }
      else if(!passo)
      {
                al_draw_scaled_bitmap(fermo2,  0, 0, al_get_bitmap_width(fermo2),  al_get_bitmap_height(fermo2), x, y, al_get_bitmap_width(fermo2)*1.5, al_get_bitmap_height(fermo2)*1.5, 0);
        cont++;

        if(cont==15)
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
  if(!al_get_timer_started(timerSalta))
  {
    al_start_timer(timerSalta);
  }

  if(!al_get_timer_started(sputaFuoco))
  {
    al_start_timer(sputaFuoco);
  }


  if(al_get_timer_count(sputaFuoco)==0)
  {
    sparaFuoco=true;
    xFuoco=x+15;
    yFuoco=y+5;
  }

  if(al_get_timer_count(timerSalta)==4)
  {
    saltando=true;
  }

  if(nColpito>=30)
  {
    vita=false;
    saltando=false;
    al_start_timer(caduta);
  }

  if(saltando && !cadendo)
  {
    saltare();
  }

  if(sparaFuoco && nColpito<30)
  {
    xFuoco-=2;
    yFuoco+=0;
    lunghezzaFuoco-=2;
    if(lunghezzaFuoco<=0)
    {
      sparaFuoco=false;
      xFuoco=-100;
      yFuoco=-100;
      lunghezzaFuoco=190;
      al_set_timer_count(sputaFuoco,0.0);
    }
  }
}

void Boss::saltare()
{
  if(saltando && saltoDistanza<=200 && !cadendo && nColpito<30) //aggiorna le posizioni per saltare
  {
    y-=5;
    saltoDistanza+=5;
    if(saltoDistanza>=200)
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
  if((a+20>=x && a-20<=x) && (b+50 >=y && b-50 <= y)) //sistemare l'intervallo
  {
    if(tipo==0)
      nColpito++;
    else
      nColpito+=5;
    return true;
  }
  return false;
}

int Boss::getTimerCaduta()
{
  if(al_get_timer_started(caduta))
    return al_get_timer_count(caduta);
  return -1;
}

void Boss::restartBoss()
{
  x=150;
  y=100;
  xFuoco=-100;
  yFuoco=-100;

  vita=true;
  nColpito=0;
  lunghezzaFuoco=250;

  saltoDistanza=0;
  cadendo=false;
  saltando=false;

  al_set_timer_count(timerSalta, 0.0);
  al_set_timer_count(sputaFuoco, 0.0);
  al_set_timer_count(caduta, 0.0);

  al_stop_timer(timerSalta);
  al_stop_timer(sputaFuoco);
  al_stop_timer(caduta);


}
