#include <iostream>
#include <string>
using namespace std;
#include "Giocatore.h"
#include "Mostro.h"
#include "Mappa.h"


void init();
void draw(string);

int main(int argc, char **argv){

  init();
  int w=1105;
  int h=1008;
  Mappa mp;
  ALLEGRO_DISPLAY       *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;

  display=al_create_display(w, h);
  timer=al_create_timer(1.0/60);


  event_queue = al_create_event_queue();

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_clear_to_color(al_map_rgb(0,0,0));
  al_flip_display();


  Giocatore * tommy= new Giocatore(w,h);
  tommy->carica_immagini();
  al_start_timer(timer);

  bool main_screen=true; //indica che ho appena aperto il gioco
  bool esc=false; //indica se chiudo il gioco dalla finestra

  //creo le mappe in base ai livelli
  Mappa mappe[2];
  mappe[1].caricaElementi("./images/objects/tile1.png");
  mappe[1].caricaMappa("./mappe/mappa1.txt");




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
      unsigned level=1;
      while(!esc)
      {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
         {
           esc=true;
           break;
         }
         else if(ev.type == ALLEGRO_EVENT_TIMER)
         {
           //fare i movimenti del giocatore
           tommy->muovi();
           //if(mappe[level].getValore((tommy->getX()/92.08), tommy->getY()/91.63))

          // cout<<tommy->getX()<<" "<<tommy->getY()<<endl;

           float a=tommy->getX()/92.08;
           int a2=tommy->getX()/92.08;


           float b=(tommy->getY()/91.63)+1;
           int b2=(tommy->getY()/91.63)+1;



           // cout<<a<<" "<<b<<" "<<mappe[level].getValore(a, b)<<" "<<tommy->getSaltando()<<endl;
           // cout<<a2<<" "<<b2<<" "<<b-b2<<endl<<endl; //non ci serve

           if(a<0)
            a=0;
            if(b<0)
              b=0;

           // if(b-b2 >= 0.1 || b-b2 <0.0)
           //  {
           //    tommy->setCadendo(true);
           //   tommy->gravita();
           //  }
           if(mappe[level].getValore(a, b)==0 && tommy->getSaltando()==false)
           {
             tommy->setCadendo(true);
            tommy->gravita();
          }
          // else if(mappe[level].getValore(a, b)==1 && b-b2 >= 0.1 || b-b2 <0.0 && tommy->getSaltando()==true)
          // {
          //   tommy->setCadendo(true);
          //  tommy->gravita();
          // }
          else
          tommy->setCadendo(false);
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

            case ALLEGRO_KEY_SPACE:
              tommy->setSaltando(true);
              tommy->setFermo(false);
              break;

            case ALLEGRO_KEY_S:
              tommy->setSaltando(true);
              tommy->setFermo(false);
              break;

         }
       }

       else if(ev.type == ALLEGRO_EVENT_KEY_UP) {  //
         switch(ev.keyboard.keycode) {

            case ALLEGRO_KEY_LEFT:
            tommy->setAndando_sinistra(false);
            tommy->setFermo(true);
               break;

            case ALLEGRO_KEY_RIGHT:
            tommy->setAndando_destra(false);
            tommy->setFermo(true);
               break;
            //
            // case ALLEGRO_KEY_SPACE:
            //  tommy->setSaltando(false);
            //  tommy->setFermo(true);
            //  break;
         }
      }

        if( redraw && al_is_event_queue_empty(event_queue))
        {
        mappe[level].drawMappa();

        tommy->drawPersonaggio();
        al_flip_display();
        }

      }
    }


  }



  //al_rest(1);
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
