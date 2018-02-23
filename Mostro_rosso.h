#ifndef MOSTRO_ROSSO
#define MOSTRO_ROSSO

class Mostro_rosso : public Mostro{
private:
  bool saltando;

public:
  ALLEGRO_BITMAP *salto;
  Mostro_rosso(int, int);

  bool getSaltando();
  void setSaltando(bool);

  void carica_immagini;

};
#endif
