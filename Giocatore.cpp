#include "Giocatore.h"
Giocatore::Giocatore(int w, int h)
{
  this->w=w;
  this->h=h;
  // x=w/2.0 - 15;
  y=h-(21*2)-15;
  x=w/2.0 - 15;
  //y=0;
  spostamento=2;
  vite=3;
  cont=0;
  parametroGravita=3;
  saltoDistanza=0;
  colpoDistanza=0;
  cont1=0;

  fermo=true;
  fermoAlternato=false;
  potere_v=false;
  andando_destra=false;
  andando_sinistra=false;
  andando_sotto=false;
  andando_sopra=false;
  saltando=false;
  sparando=false;
  passo=false;
  cadendo=false;
  toccato=false;
  spostaMostro=false;
  potere_v=false;
  trasformazione=al_create_timer(1.0/10);


  salta= NULL;

	verso_sinistra1= NULL;
	verso_sinistra2= NULL;
  lancia_sinistra1=NULL;
  lancia_sinistra2=NULL;

	verso_destra1= NULL;
	verso_destra2= NULL;
  lancia_destra1=NULL;
  lancia_destra2=NULL;
}

Giocatore::~Giocatore()
{
  al_destroy_bitmap(salta);
  al_destroy_bitmap(fermo_destra);
  al_destroy_bitmap(fermo_sinistra);
  al_destroy_bitmap(verso_sinistra1);
  al_destroy_bitmap(verso_sinistra2);
  al_destroy_bitmap(verso_destra1);
  al_destroy_bitmap(verso_destra2);
  al_destroy_bitmap(lancia_sinistra1);
  al_destroy_bitmap(lancia_sinistra2);
  al_destroy_bitmap(lancia_destra1);
  al_destroy_bitmap(lancia_destra2);
}

//************//
//SEZIONE SETS//
//************//
void Giocatore::setX(unsigned sx)
{
  x=sx;
}

void Giocatore::setY(unsigned sy)
{
  y=sy;
}

void Giocatore::setVelocita(unsigned v)
{
  velocita=v;
}

void Giocatore::setVite(unsigned v)
{
  vite=v;
}

void Giocatore::setAndando_destra(bool d)
{
  andando_destra=d;
}

void Giocatore::setAndando_sinistra(bool s)
{
  andando_sinistra=s;
}

void Giocatore::setAndando_sopra(bool s)
{
  andando_sopra=s;
}
void Giocatore::setAndando_sotto(bool s)
{
  andando_sotto=s;
}

void Giocatore::setSaltando(bool s)
{
  saltando=s;
}

void Giocatore::setSparando(bool s)
{
  sparando=s;
}

void Giocatore::setFermo(bool s)
{
  fermo=s;
}

void Giocatore::setPasso(bool s)
{
  passo=s;
}

void Giocatore::setToccato(bool s)
{
  toccato=s;
}

void Giocatore::setPotere(bool p)
{
  potere_v=p;
}
void Giocatore::setCadendo(bool s)
{
  cadendo=s;
}

void Giocatore::setSpostaMostro(bool s)
{
  spostaMostro=s;
}

void Giocatore::setCont1(unsigned c)
{
  cont1=c;
}

//************//
//SEZIONE GETS//
//************//

float Giocatore::getX()
{
  return x;
}

float Giocatore::getY()
{
  return y;
}

unsigned Giocatore::getVelocita()
{
  return velocita;
}
unsigned  Giocatore::getVite()
{
  return vite;
}

bool Giocatore::getAndando_destra()
{
  return andando_destra;
}

bool Giocatore::getAndando_sinistra()
{
  return andando_sinistra;
}

bool Giocatore::getAndando_sopra()
{
  return andando_sopra;
}
bool Giocatore::getAndando_sotto()
{
  return andando_sotto;
}

bool Giocatore::getSaltando()
{
  return saltando;
}

bool Giocatore::getSparando()
{
  return sparando;
}

bool Giocatore::getCadendo()
{
  return cadendo;
}

bool Giocatore::getFermoalternato(){
return fermoAlternato;
}

bool Giocatore::getToccato(){
  return toccato;
}

int Giocatore::getCont(){
  return cont;
}

unsigned Giocatore::getSpostamento()
{
  return spostamento;
}

unsigned Giocatore::getCont1(){
  return cont1;
}

bool Giocatore::getSpostaMostro()
{
  return spostaMostro;
}

bool Giocatore::getPotere()
{
  return potere_v;
}




//IMMAGINI E DISEGNO

void Giocatore::carica_immagini()
{
  salta= al_load_bitmap("./images/giocatore/salto.png");

  fermo_destra=al_load_bitmap("./images/giocatore/fermo_dx.png");
  fermo_sinistra=al_load_bitmap("./images/giocatore/fermo_sx.png");

	verso_sinistra1= al_load_bitmap("./images/giocatore/sinistra_1.png");
	verso_sinistra2= al_load_bitmap("./images/giocatore/sinstra_2.png");
	//verso_sinistra3= al_load_bitmap("./images/giocatore/");

	verso_destra1= al_load_bitmap("./images/giocatore/destra_dx1.png");
	verso_destra2= al_load_bitmap("./images/giocatore/destra_2.png");
	//verso_destra3= al_load_bitmap("./images/giocatore/");


  lancia_sinistra1=al_load_bitmap("./images/giocatore/lancia_sx2.png");
  lancia_sinistra2=al_load_bitmap("./images/giocatore/lancia_sx3.png");
  lancia_destra1=al_load_bitmap("./images/giocatore/lancia_dx2.png");
  lancia_destra2=al_load_bitmap("./images/giocatore/lancia_dx3.png");

  sposta_verso_sinistra1=al_load_bitmap("./images/giocatore/spinge_sx1.png");
  sposta_verso_sinistra2=al_load_bitmap("./images/giocatore/spinge_sx2.png");
  sposta_verso_destra1=al_load_bitmap("./images/giocatore/spinge_dx1.png");
  sposta_verso_destra2=al_load_bitmap("./images/giocatore/spinge_dx2.png");

  toccato1=al_load_bitmap("./images/giocatore/toccato1.png");
  toccato2=al_load_bitmap("./images/giocatore/toccato2.png");
  toccato3=al_load_bitmap("./images/giocatore/toccato3.png");
  lanterna=al_load_bitmap("./images/objects/lantern_v1.png");

  trasformazione1dx=al_load_bitmap("./images/giocatore/diventaGrande_dx1.png");
  trasformazione2dx=al_load_bitmap("./images/giocatore/diventaGrande_dx2.png");
  trasformazione3dx=al_load_bitmap("./images/giocatore/diventaGrande_dx3.png");
  trasformazione1sx=al_load_bitmap("./images/giocatore/diventaGrande_sx1.png");
  trasformazione2sx=al_load_bitmap("./images/giocatore/diventaGrande_sx2.png");
  trasformazione3sx=al_load_bitmap("./images/giocatore/diventaGrande_sx3.png");

  grande_fermo1=al_load_bitmap("./images/giocatore/grande_fermo1.png");
  grande_fermo2=al_load_bitmap("./images/giocatore/grande_fermo2.png");
  grande_destra1=al_load_bitmap("./images/giocatore/grande_dx1.png");
  grande_destra2=al_load_bitmap("./images/giocatore/grande_dx2.png");
  grande_sinistra1=al_load_bitmap("./images/giocatore/grande_sx1.png");
  grande_sinistra2=al_load_bitmap("./images/giocatore/grande_sx2.png");
}

void Giocatore::drawPersonaggio()
{
  if(potere_v)
  {
    if(al_get_timer_count(trasformazione)>=3)
    {
      if(andando_destra && passo)
      {
        al_draw_bitmap(grande_destra1, x, y,0);
        cont++;

        if(cont==7)
        {
          passo=false;
          cont=0;
        }
        fermoAlternato=true;
      }
      else if(andando_destra && !passo )
      {
         al_draw_bitmap(grande_destra2, x, y, 0);
        cont++;

        if(cont==7)
        {
          passo=true;
          cont=0;

        }
        fermoAlternato=true;
      }
      else if(andando_sinistra && passo )
      {
         al_draw_bitmap(grande_sinistra1, x, y, 0);
        cont++;

        if(cont==7)
        {
          passo=false;
          cont=0;
        }
        fermoAlternato=false;
      }

      else if(andando_sinistra && !passo )
      {
         al_draw_bitmap(grande_sinistra2, x, y, 0);
        cont++;

        if(cont==7)
        {
          passo=true;
          cont=0;
        }
        fermoAlternato=false;
      }
      else if((andando_sopra || andando_sotto||fermo) && passo )
      {
         al_draw_bitmap(grande_fermo1, x, y, 0);
        cont++;

        if(cont==7)
        {
          passo=false;
          cont=0;
        }
      }
      else if((andando_sopra || andando_sotto||fermo) && !passo )
      {
         al_draw_bitmap(grande_fermo2, x, y,0);
        cont++;

        if(cont==7)
        {
          passo=true;
          cont=0;
        }
      }
    }
    else
    {
      if(al_get_timer_count(trasformazione)==0)
      {
        if(andando_destra)
           al_draw_bitmap(trasformazione1dx, x, y, 0);
        else
           al_draw_bitmap(trasformazione1sx,  x, y, 0);
      }
      else if(al_get_timer_count(trasformazione)==1)
      {
        if(andando_destra)
           al_draw_bitmap(trasformazione2dx,   x, y,   0);
        else
           al_draw_bitmap(trasformazione2sx,   x, y,   0);
      }
      else if(al_get_timer_count(trasformazione)==2)
      {
        if(andando_destra)
           al_draw_bitmap(trasformazione3dx,   x, y, 0);
        else
           al_draw_bitmap(trasformazione3sx,   x, y, 0);
      }
    }
  }
  else
  {

  if(toccato)
 {
   if(cont1<=20)
    {
       al_draw_bitmap(toccato1,   x, y, 0);
      cont1++;
    }
   else if(cont1 >20 && cont1<=40)
   {
      al_draw_bitmap(toccato2,   x, y, 0);
     cont1++;
   }
   else if(cont1 >40 && cont1<=60)
   {
      al_draw_bitmap(toccato3,   x, y, 0);
     cont1++;
   }
   else if(cont1>60)
   toccato=false;
 }
else
{
 if(fermo && fermoAlternato && !andando_destra && !andando_sinistra && !cadendo && !toccato)
  {
    if(sparando && passo)
       al_draw_bitmap(lancia_destra1,   x, y, 0);
    else if(sparando && !passo)
     al_draw_bitmap(lancia_destra2,   x, y, 0);

    else
       al_draw_bitmap(fermo_destra,   x, y, 0);
    cont++;

    if(cont==7)
     {
       if(passo)
        passo=false;
        else
        passo=true;
       cont=0;
     }
  }

  else if(fermo && !fermoAlternato && !andando_destra && !andando_sinistra && !cadendo && !toccato)
  {
    if(sparando && passo)
       al_draw_bitmap(lancia_sinistra1,   x, y, 0);
    if(sparando & !passo)
     al_draw_bitmap(lancia_sinistra2,   x, y, 0);

    else
       al_draw_bitmap(fermo_sinistra,   x, y, 0);

    cont++;

    if(cont==7)
     {
       if(passo)
        passo=false;
        else
        passo=true;
       cont=0;
     }
  }

  else if(saltando && !andando_destra && !andando_sinistra && !cadendo && !toccato)
  {
    if(sparando)
       al_draw_bitmap(lancia_destra1,   x, y, 0);
    else
     al_draw_bitmap(salta,   x, y, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }

  }

   if(cadendo && !toccato)
   {
    if(sparando)
       al_draw_bitmap(lancia_destra1,   x, y, 0);
    else
       al_draw_bitmap(salta,   x, y, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }
   }

  else if(andando_destra && !passo && !toccato)
    {
      if(sparando)
         al_draw_bitmap(lancia_destra1,   x, y, 0);
      else if(spostaMostro)
        {
           al_draw_bitmap(sposta_verso_destra1,   x, y, 0);
        }
      else if(!spostaMostro)
           al_draw_bitmap(verso_destra1,   x, y, 0);
      cont++;

      if(cont==7)
       {
         passo=true;
         cont=0;
       }
       fermoAlternato=true;
    }

  else if(andando_destra && passo && !toccato )
    {
      if(sparando)
         al_draw_bitmap(lancia_destra2,   x, y, 0);
        else if(spostaMostro)
          {
             al_draw_bitmap(sposta_verso_destra2,   x, y, 0);
          }
          else if(!spostaMostro)
             al_draw_bitmap(verso_destra2,   x, y, 0);
      cont++;

      if(cont==7)
      {
        passo=false;
        cont=0;
      }
      fermoAlternato=true;
    }

  else if(andando_sinistra && !passo && !toccato)
  {
    if(sparando)
       al_draw_bitmap(lancia_sinistra1,   x, y, 0);
      else if(spostaMostro)
        {
           al_draw_bitmap(sposta_verso_sinistra1,   x, y, 0);
        }
        else if(!spostaMostro)
           al_draw_bitmap(verso_sinistra1,   x, y, 0);
    cont++;

    if(cont==7)
     {
       passo=true;
       cont=0;
     }
     fermoAlternato=false;
  }

  else if(andando_sinistra && passo &&!toccato)
  {
    if(sparando)
       al_draw_bitmap(lancia_sinistra2,   x, y, 0);
      else if(spostaMostro)
        {
           al_draw_bitmap(sposta_verso_sinistra2,   x, y, 0);
        }
        else if(!spostaMostro)
           al_draw_bitmap(verso_sinistra2,   x, y, 0);
    cont++;

    if(cont==7)
    {
      passo=false;
      cont=0;
    }

    fermoAlternato=false;
  }
}
}
}

void Giocatore::drawLanterna(float posX, float posY)
{
   al_draw_bitmap(lanterna,posX, posY, 0);
}
//MOVIMENTI

void Giocatore::muovi()
{
  if(potere_v)
  {
    if(andando_sopra && y>0)
    {
      y-=spostamento;
    }
    if(andando_sotto && y<231)
    {
      y+=spostamento;
    }
   if(andando_destra && x<=w-spostamento) //movimento a dx aggiorna la x che corrisponde alla larghezza schermo
    {
      x+=spostamento;
    }

   if(andando_sinistra && x>0) //movimento a sx
      x-=spostamento;
  }
  else
  {
    if(andando_destra && x+24<=w-spostamento&&!toccato) //movimento a dx aggiorna la x che corrisponde alla larghezza schermo
    {
      x+=spostamento;
    }

    else if(andando_sinistra && x+6>0&&!toccato) //movimento a sx
      x-=spostamento;


    if(saltando && saltoDistanza<=42 && !cadendo&&!toccato) //aggiorna le posizioni per saltare
    {
      y-=5;
      saltoDistanza+=5;
      if(saltoDistanza>=42)
      {
        saltando=false;
        fermo=false;
        saltoDistanza=0;
        cadendo=true;
      }
    }
  }

 }




void Giocatore::gravita()
{
  y+=parametroGravita;
}

bool Giocatore::controllaTocco(int a,int b, bool i,bool c){

  if(fermoAlternato)
  {
    if(x+25 > a && b+20 >= static_cast<int>(y) && b-20 <= static_cast<int>(y) && i && x<a)
    {
      //cout<<"tocco DX"<<endl;
      spostaMostro=true;
      return true;
    }
    else
    {
      //cout<<"NO tocco DX"<<endl;
      spostaMostro=false;
      return false;
    }
  }
  else if(!fermoAlternato)
  {
    if(x-20 < a && b+20 >= static_cast<int>(y) && b-20 <= static_cast<int>(y) && i && x>a)
    {
      //cout<<"tocco SX"<<endl;
      spostaMostro=true;
      return true;
    }
    else
    {
      //cout<<"NO tocco SX"<<endl;
      spostaMostro=false;
      return false;
    }
  }
  //cout<<"niente"<<endl;
  return false;
}

void Giocatore::controllaseToccato(int a,int b)
{
  if((a+10>=static_cast<int>(x) && a-10<=static_cast<int>(x)) && b+20 >= static_cast<int>(y) && b-20 <= static_cast<int>(y))
  {
    toccato=true;
    fermo=false;
    andando_destra=false;
    andando_sinistra=false;
    saltando=false;
    sparando=false;
    potere_v=false;
    vite--;
  }
}

bool Giocatore::controllaseToccatoSushi(int a, int b)
{
  if((a+12>=static_cast<int>(x) && a-20<=static_cast<int>(x)) && b+20 >= static_cast<int>(y) && b-20 <= static_cast<int>(y))
  {
    return true;
  }
  return false;
}

void Giocatore::presaLanterna(int a, int b)
{
  if((a+12>=static_cast<int>(x) && a-20<=static_cast<int>(x)) && b+20 >= static_cast<int>(y) && b-20 <= static_cast<int>(y))
  {
    potere_v=true;
      al_start_timer(trasformazione);
  }
}

void Giocatore::disattivaPotere()
{
  potere_v=false;
  al_set_timer_count(trasformazione,0.0);
  al_stop_timer(trasformazione);
}
