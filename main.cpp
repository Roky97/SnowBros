#include <iostream>
#include <string>
using namespace std;
#include "Giocatore.h"
#include "Mostro.h"
#include "Mappa.h"
#include "Colpo.h"
#include "Mostro_rosso.h"

const int ncolpi=10;
const int maxmostri=100;


void init();
void draw(string);

int main(int argc, char **argv){

  init();
  int w=1105;
  int h=1008;
  unsigned level=0;
  int nMostri=0;
  ALLEGRO_DISPLAY       *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  Colpo colpi[ncolpi];
  Mappa mappe[2];
  Mostro *mostri[maxmostri];
  Giocatore * tommy= new Giocatore(w,h);
  bool main_screen=true;
  bool esc=false;
  bool mostrivivi=true;
  bool restart=false;








  display=al_create_display(w, h);
  timer=al_create_timer(1.0/60);
  event_queue = al_create_event_queue();

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_clear_to_color(al_map_rgb(0,0,0));
  al_flip_display();
  al_start_timer(timer);

  tommy->carica_immagini();
  mappe[0].caricaElementi("./images/objects/tile1.png");
  mappe[0].caricaMappa("./mappe/mappa1.txt");



  for(int i=0;i<mappe[0].getMapSizeX();i++)
  {
    for(int j=0;j<mappe[0].getMapSizeY();j++)
    {
      switch (mappe[0].getValore(i,j)) {
        case 2:
        mostri[nMostri]=new Mostro_rosso();
        mostri[nMostri]->setX(i*92.08);
        mostri[nMostri]->setY(j*91.63);
        mostri[nMostri]->carica_immagini();
        nMostri++;
        break;
        // /case 3:
        // mostri[nMostri]=new Mostro_giallo(i*92.08,j*91.63);
        // nMostri++;
        // break;
      }
    }
  }







  while(!esc)
  {
  // al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);

    if(main_screen)
    {
      bool screen=0;
      bool redraw=true;
      ALLEGRO_BITMAP* schermata1= al_load_bitmap("./images/schermata_iniziale/schermata_iniziale_1.png");
      ALLEGRO_BITMAP* schermata2= al_load_bitmap("./images/schermata_iniziale/schermata_iniziale_2.png");

      while(main_screen)
      {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
         {
           main_screen=false;
           esc=true;
           al_destroy_bitmap(schermata1);
           al_destroy_bitmap(schermata2);
           break;
         }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
          switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ENTER:
            main_screen=false;
            redraw=false;
            al_destroy_bitmap(schermata1);
            al_destroy_bitmap(schermata2);
            break;
          }
        if(screen && redraw && al_is_event_queue_empty(event_queue))
        {
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_scaled_bitmap(schermata1, 0, 0, 256, 224, 0,0,w,h,0);
          al_flip_display();
          al_rest(0.5);
          screen=false;

        }
        else if(!screen && redraw && al_is_event_queue_empty(event_queue))
        {
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_scaled_bitmap(schermata2, 0, 0, 256, 224, 0,0,w,h,0);
          al_flip_display();
          al_rest(0.5);
          screen=true;
        }
      }
    }



    if(!esc)
    {
      bool redraw=true;
      while(!esc)
      {
         /*if(restart)
         {
           tommy->setX(w/2.0 - 15);
           tommy->setY(h-30*4 -21*(4));
           tommy->setToccato(false);
           restart=false;
         }*/



        al_clear_to_color(al_map_rgb(0,0,0));
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
         {
           esc=true;
           break;
         }

         else if(ev.type == ALLEGRO_EVENT_TIMER)
         {
           tommy->muovi(); //aggiorno la posizione del giocatore

           // for(int i=0;i<nMostri;i++)
           // {
           //   tommy->controllaTocco(mostri[i]->getX(),mostri[i]->getY());
           //   if(tommy->getToccato())
           //   {
           // tommy->setVite(tommy->getVite()-1);
           //     //restart=true;
           //     break;
           //   }
           // }


          for(int i=0; i<ncolpi; i++) //aggiorno la posizione dei colpi
          {
            colpi[i].updateColpo();
          }

          for(int i=0;i<nMostri;i++) //aggiorno la posizione dei mostri
          {
            if(mostri[i]->getVita())
              mostri[i]->muovi();
          }

          float a=tommy->getX()/92.08;
          float b=(tommy->getY()/91.63)+1;

          if(a<0)
            a=0;

          if(b<0)
            b=0;

          if(mappe[level].getValore(a, b)!=1 && tommy->getSaltando()==false) //gravita'
          {
            tommy->setCadendo(true);
            tommy->gravita();
          }
          else
          {
            tommy->setCadendo(false);
            tommy->setFermo(true);
          }

          for(int i=0; i<nMostri; i++)
          {
            if(mostri[i]->getVita())
            {
            float ma=mostri[i]->getX()/92.08;
            float mb=(mostri[i]->getY()/91.63)+1;
            if(ma<0)
              ma=0;
            if(mb<0)
              mb=0;

              if(tommy->controllaTocco(mostri[i]->getX(), mostri[i]->getY(), mostri[i]->getTotInnevato())) //tommy sposta i mostri solo se sono totalmente innevati
                mostri[i]->muoviDaTommySeInnevato(tommy->getAndando_destra(), tommy->getAndando_sinistra(),  tommy->getSpostamento());

              if(mappe[level].getValore(ma, mb)!=1 && mostri[i]->getSaltando()==false) //gravita' dei mostri
              {
                mostri[i]->setCadendo(true);
                mostri[i]->gravita();
              }
              else
              {
                mostri[i]->setCadendo(false);
              }

              if(mostri[i]->getContPrimaDiSaltare()==0 && mappe[level].getValore(ma, mb-2)==1) //salto dei mostri
                mostri[i]->setSaltando(true);
              }

              //fare la collisione tra il giocatore e il nemico
            }


           for(int i=0; i<nMostri; i++) //controllo la collisione tra i colpi e i mostri
           {
             if(mostri[i]->getVita())
             {
               for(int j=0; j<ncolpi; j++)
               {
                 if(colpi[j].getVita())
                  if(mostri[i]->collisioneProiettile(colpi[j].getX(), colpi[j].getY()))
                    colpi[j].setVita(false);
                }
            }
           }


           for(int i=0; i<nMostri; i++)
           {
             if(mostri[i]->getVita())
             {
               for(int j=0; j<nMostri; j++)
               {
                 if(mostri[j]->getVita())
                 {

                   // if(i!=j)
                   //cout<<i<<" "<<mostri[i]->getY()<<" - "<<j<<" "<<mostri[j]->getY()<<endl<<endl;
                   if( mostri[i]->controllaSeToccato(mostri[j]->getX(), mostri[j]->getY(), mostri[j]->getAndando_destra(), mostri[j]->getAndando_sinistra())) //devo controllare ch ei mostri sono anche vivi
                   {
                     if(mostri[i]->getAndando_destra())
                     {
                       mostri[i]->setAndando_destra(false);
                       mostri[i]->setAndando_sinistra(true);

                       mostri[j]->setAndando_destra(true);
                       mostri[j]->setAndando_sinistra(false);

                       mostri[i]->setX(mostri[i]->getX()-35);
                       mostri[j]->setX(mostri[j]->getX()+35);

                       mostri[i]->diminuisciContPrimaDiSaltare();
                       mostri[j]->diminuisciContPrimaDiSaltare();
                     }
                     else if(mostri[j]->getAndando_destra())
                     {
                       mostri[i]->setAndando_destra(true);
                       mostri[i]->setAndando_sinistra(false);

                       mostri[j]->setAndando_destra(false);
                       mostri[j]->setAndando_sinistra(true);

                       mostri[i]->setX(mostri[i]->getX()+35);
                       mostri[j]->setX(mostri[j]->getX()-35);

                      mostri[i]->diminuisciContPrimaDiSaltare();
                      mostri[j]->diminuisciContPrimaDiSaltare();
                    }

                    if(mostri[j]->getTotInnevato() || mostri[i]->getTotInnevato()) //quando un mostro sta per morire e colpisce uno non innevato, quest'ultimo morira' pure
                    {
                      mostri[i]->setTotInnevato(true);
                      mostri[i]->setcolpitoInnevato(true);

                      mostri[j]->setTotInnevato(true);
                      mostri[j]->setcolpitoInnevato(true);
                    }
                  }
                }
              }
              }
           }


         }


         else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {

            case ALLEGRO_KEY_LEFT:
               tommy->setAndando_sinistra(true);
               tommy->setFermo(false);
               break;

            case ALLEGRO_KEY_RIGHT:
              tommy->setAndando_destra(true);
              tommy->setFermo(false);
               break;

            case ALLEGRO_KEY_UP:
            if(tommy->getCadendo()==false)
              {
                tommy->setSaltando(true);
                tommy->setFermo(false);
              }
              break;

            case ALLEGRO_KEY_A:
            tommy->setSparando(true);
            for(int i=0;i<ncolpi && !colpi[i].fireColpo(tommy->getX(),tommy->getY(),tommy->getFermoalternato());i++);
            break;
         }
       }

       else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {

            case ALLEGRO_KEY_LEFT:
            tommy->setAndando_sinistra(false);
            tommy->setFermo(true);
              break;

            case ALLEGRO_KEY_RIGHT:
            tommy->setAndando_destra(false);
            tommy->setFermo(true);
               break;

             case ALLEGRO_KEY_A:
             tommy->setSparando(false);
             break;
         }
      }

        if( redraw && al_is_event_queue_empty(event_queue))
        {


        mappe[level].drawMappa();

        for(int i=0;i<nMostri;i++)
          if(mostri[i]->getVita())
          {
            mostri[i]->drawMostro();
          }

        tommy->drawPersonaggio();

        for(int i=0;i<ncolpi;i++)
        {
          colpi[i].drawColpo();
        }

        al_flip_display();
        }

      }
    }
  }


  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(event_queue);
  delete tommy;

  return 0;
}

void init()
{
  al_init();
  al_init_image_addon();
  al_init_primitives_addon();
  al_install_keyboard();
}
