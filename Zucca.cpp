#include "Zucca.h"

Zucca::Zucca()
{
  x=0;
  y=0;
  cont=0;
  changeBitmap=false;
  spostamento=7;
  vita=false;
  andando_destra=false;
  andando_sinistra=false;
  dx1=al_load_bitmap("./images/zucca/destra1.png");
  dx2=al_load_bitmap("./images/zucca/destra2.png");

  sx1=al_load_bitmap("./images/zucca/sinistra1.png");
  sx2=al_load_bitmap("./images/zucca/sinistra2.png");
}

Zucca::Zucca(float posx, float posy)
{
  x=posx;
  y=posy;
  cont=0;
  changeBitmap=false;
  spostamento=3;
  vita=false;
  andando_destra=false;
  andando_sinistra=false;
  dx1=al_load_bitmap("./images/zucca/destra1.png");
  dx2=al_load_bitmap("./images/zucca/destra2.png");

  sx1=al_load_bitmap("./images/zucca/sinistra1.png");
  sx2=al_load_bitmap("./images/zucca/sinistra2.png");
}

Zucca::~Zucca()
{
  al_destroy_bitmap(dx1);
  al_destroy_bitmap(dx2);
  al_destroy_bitmap(sx1);
  al_destroy_bitmap(sx2);
}


void Zucca::setVita(bool v)
{
  vita=v;
}

void Zucca::setX(float posx)
{
  x=posx;
}

void Zucca::setY(float posy)
{
  y=posy;
}

bool Zucca::getVita()
{
  return vita;
}

float Zucca::getX()
{
  return x;
}

float Zucca::getY()
{
  return y;
}

void Zucca::muoviZucca(float posX, float posY) //PASSIAMO LE POSIZIONI DEL PERSONAGGIO IN MODO DA RAGGIUNGERLO OVUNQUE ESSO SIA
{
  if(posX-50<=x && posX+50>=x)
  {
    if(posY<y)
    {
    y-=spostamento;
    andando_sinistra=true;
    andando_destra=false;
    }
    if(posY>y)
    {
    y+=spostamento;
    andando_destra=true;
    andando_sinistra=false;
    }
  }
  else
  {
    if(posX>x && posY>y)
    {
      x+=spostamento;
      y+=spostamento;
      andando_destra=true;
      andando_sinistra=false;
    }
    else if(posX>x && posY<y)
    {
      x+=spostamento;
      y-=spostamento;
      andando_destra=true;
      andando_sinistra=false;
    }
    else if(posX<x && posY>y)
    {
      x-=spostamento;
      y+=spostamento;
      andando_sinistra=true;
      andando_destra=false;
    }
   else if(posX<x && posY<y)
    {
      x-=spostamento;
      y-=spostamento;
     andando_sinistra=true;
     andando_destra=false;
    }
   else if(posX<x && posY==y)
   {
     x-=spostamento;
     andando_sinistra=true;
     andando_destra=false;
   }
   else if(posX>x && posY==y)
   {
     x+=spostamento;
     andando_sinistra=false;
     andando_destra=true;
   }
 }
}
void Zucca::drawZucca()
{
  if(andando_destra && !changeBitmap)
  {
      al_draw_scaled_bitmap(dx1, 0, 0, 30, 30, x, y, 30*6, 30*6, 0);
      cont++;

       if(cont==7)
       {
       changeBitmap=true;
       cont=0;
       }
  }


  else if(andando_destra && changeBitmap)
  {
      al_draw_scaled_bitmap(dx2, 0, 0, 30, 30, x, y, 30*6, 30*6, 0);
      cont++;

       if(cont==7)
       {
        changeBitmap=false;
        cont=0;
       }
  }

  else if(andando_sinistra && !changeBitmap)
  {
    al_draw_scaled_bitmap(sx1, 0, 0, 30, 30, x, y, 30*6, 30*6, 0);
    cont++;

     if(cont==7)
     {
     changeBitmap=true;
     cont=0;
     }
  }

  else if(andando_sinistra && changeBitmap)
  {
    al_draw_scaled_bitmap(sx2, 0, 0, 30, 30, x, y, 30*6, 30*6, 0);
    cont++;

     if(cont==7)
     {
     changeBitmap=false;
     cont=0;
     }
  }
}
