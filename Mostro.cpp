#include "Mostro.h"

Mostro::Mostro(){
  spostamento=1.5;
  x=0;
  y=0;
  passo=false;
  cont=0;
  parametroGravita=3;
  colpito=false;
  colpitoInnevato=false;
  totInnevato=false;
  saltoDistanza=0;
  vita=true;
  sushi=false;
  contPrimaDiSaltare=500;
  cadendo=false;

  verso_sinistra1= NULL;
  verso_sinistra2= NULL;
  colpito_sinistra1=NULL;
  colpito_sinistra2=NULL;

	verso_destra1= NULL;
	verso_destra2= NULL;
  colpito_destra1=NULL;
  colpito_destra2=NULL;

  innevando1=al_load_bitmap("./images/neve/innevando1.png");
  innevando2=al_load_bitmap("./images/neve/innevando2.png");
  innevando3=al_load_bitmap("./images/neve/innevando3.png");
  palladineve1=al_load_bitmap("./images/neve/palladineve1.png");
  palladineve2=al_load_bitmap("./images/neve/palladineve2.png");
  im_sushi[0]=al_load_bitmap("./images/objects/sushi/sushi1.png");
  im_sushi[1]=al_load_bitmap("./images/objects/sushi/sushi2.png");
  im_sushi[2]=al_load_bitmap("./images/objects/sushi/sushi3.png");
  im_sushi[3]=al_load_bitmap("./images/objects/sushi/sushi4.png");
  im_sushi[4]=al_load_bitmap("./images/objects/sushi/sushi5.png");


  congelo=al_create_timer(1.0/5);

  salta=NULL;
  //al_start_timer(congelo);

  srand((unsigned)time(NULL));

  contPrimaDiSaltare=rand()%3+3;

  int a=rand()%1001;

  if(a%2==0)
    andando_sinistra=true;

  if(andando_sinistra)
    andando_destra=false;
  else
    andando_destra=true;

}
Mostro::Mostro(float posx, float posy)
{
  x=posx;
  y=posy;
  spostamento=1.5;

  andando_sinistra=false;
  passo=false;
  sushi=false;
  cont=0;

	verso_sinistra1= NULL;
	verso_sinistra2= NULL;

	verso_destra1= NULL;
	verso_destra2= NULL;
  im_sushi[0]=al_load_bitmap("./images/objects/sushi/sushi1.png");
  im_sushi[1]=al_load_bitmap("./images/objects/sushi/sushi2.png");
  im_sushi[2]=al_load_bitmap("./images/objects/sushi/sushi3.png");
  im_sushi[3]=al_load_bitmap("./images/objects/sushi/sushi4.png");
  im_sushi[4]=al_load_bitmap("./images/objects/sushi/sushi5.png");
}

Mostro::~Mostro()
{
  al_destroy_bitmap(innevando1);
  al_destroy_bitmap(innevando2);
  al_destroy_bitmap(innevando3);
  al_destroy_bitmap(palladineve1);
  al_destroy_bitmap(palladineve2);


}

//SETS
void Mostro::setX(float sx)
{
  x=sx;
}

void Mostro::setY(float sy)
{
  y=sy;
}

void Mostro::setVita(bool v){
  vita=v;
}


void Mostro::setAndando_destra(bool d)
{
  andando_destra=d;
}
void Mostro::setAndando_sinistra(bool s)
{
  andando_sinistra=s;
}

void Mostro::setSaltando(bool s)
{
  saltando=s;
}

void Mostro::setCadendo(bool c)
{
  cadendo=c;
}

void Mostro::setColpito(bool c)
{
  colpito=c;
}

void Mostro::setContPrimaDiSaltare(unsigned c)
{
  contPrimaDiSaltare=c;
}

void Mostro::setTotInnevato(bool i)
{
  totInnevato=i;
}

void Mostro::setcolpitoInnevato(bool i)
{
  colpitoInnevato=true;
}

void Mostro::setnColpito(unsigned c){

nColpito=c;
}

void Mostro::setSushi(bool s)
{
  sushi=s;
}


//GETS
float Mostro::getX()
{
  return x;
}
float Mostro::getY()
{
  return y;
}

bool Mostro::getAndando_destra()
{
  return andando_destra;
}
bool Mostro::getAndando_sinistra()
{
  return andando_sinistra;
}

bool Mostro::getVita(){
  return vita;
}

bool Mostro::getSaltando()
{
    return saltando;
}
bool Mostro::getCadendo()
{
  return cadendo;
}

bool Mostro::getColpito()
{
  return colpito;
}

unsigned Mostro::getContPrimaDiSaltare()
{
  return contPrimaDiSaltare;
}

bool Mostro::getTotInnevato()
{
  return totInnevato;
}

unsigned Mostro::getnColpito(){
  return nColpito;
}

bool Mostro::getcolpitoInnevato(){
  return colpitoInnevato;
}

int Mostro::getTipo()
{
  return tipo;
}
int Mostro::getxFuoco()
{
  return xFuoco;
}

int Mostro::getyFuoco()
{
  return yFuoco;
}

bool Mostro::getSushi()
{
  return sushi;
}

void Mostro::gravita()
{
    y+=parametroGravita;
}

void Mostro::diminuisciContPrimaDiSaltare()
{
  if(contPrimaDiSaltare>0)
    contPrimaDiSaltare-=1;
}

void Mostro::muoviDaTommySeInnevato(bool dest, bool sini, unsigned spost)
{
  if(totInnevato)
  {
    if(dest)
    {
      x+=spost;
      andando_destra=true;
      andando_sinistra=false;
    }
    else if(sini)
    {
      x-=spost;
      andando_destra=false;
      andando_sinistra=true;
    }
  }
}

bool Mostro::controllaSeToccato(int a, int b, bool dest, bool sin)
{
  //if((andando_destra && sin) || (andando_sinistra && dest))
  //{
    if((a+6>=static_cast<int>(x) && a-6<=static_cast<int>(x)) && b+20 >= static_cast<int>(y) && b-20 <= static_cast<int>(y) )
    {
      return true;
    }
  //}
  return false;
}

bool Mostro::collisioneProiettile(int a, int b, bool dir)
{
  // a+=1;
  // b+=2;
  //if(a <= static_cast<int>(x) && a + 10 >= static_cast<int>(x) && b >= y && b <= (y+100))
    if((a+15>=static_cast<int>(x) && a-15<=static_cast<int>(x)) && b+20 >= static_cast<int>(y) && b-20 <= static_cast<int>(y) )
    {
    //al_start_timer(congelo);
    colpito=true;
    if(totInnevato)
      {
        colpitoInnevato=true;
        if(dir)
        {
          andando_destra=true;
          andando_sinistra=false;
        }
        else
        {
          andando_destra=false;
          andando_sinistra=true;
        }
      }
    if(nColpito<=20)
      nColpito+=2;
    if(nColpito>=7)
      totInnevato=true;
    return true;
    }
  return false;
}

void Mostro::drawSushi()
{
  if(sushi)
  {
    srand(time(0));

    if(andando_destra)
      al_draw_bitmap(im_sushi[iSushi], x-10, y,  0);
    else
      al_draw_bitmap(im_sushi[iSushi], x+10, y,  0);

  }
}

void Mostro::colpitoEdInnevato()
{
  parametroGravita=6;
  if(andando_destra)
  {
    if(x+9>=252)
      {
        sconfitto();
      } //qua caso mai facciamo una animazione
    x+=spostamento+6;
  }
  else if(andando_sinistra)
  {
    if(x<0)
      {

        sconfitto();

      }
    x-=spostamento+6;
  }
}

void Mostro::sconfitto()
{
  vita=false;
  if(andando_destra)
  {
    y+=7;
    x-=15;
  }
  else
  {
    y+=7;
    x+=15;
  }
  sushi=true;
  iSushi=rand()%4;
  totInnevato=false;
  colpito=false;
  nColpito=0;
  colpitoInnevato=false;
}
