#include "Mostro_rosso"

Mostro_rosso(int x, int y)
{
  Mostro(x,y);
  saltando=false;
  salto=NULL;
}

bool getSaltando()
{
  return saltando;
}

void setSaltando(bool s)
{
  saltando=s;
}

void carica_immagini()
{
  verso_sinistra1=al_load_bitmap(".images/mostro_rosso/sinistra_1.png");
  verso_sinistra2=al_load_bitmap(".images/mostro_rosso/sinistra_2.png");

  verso_destra1=al_load_bitmap(".images/mostro_rosso/destra_1.png");
  verso_destra1=al_load_bitmap(".images/mostro_rosso/destra_1.png");

  salto=al_load_bitmap(".images/mostro_rosso/salto.png");
}
