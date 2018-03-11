#include <iostream>
#include <string>
using namespace std;
#include "Giocatore.h"
#include "Mostro.h"
#include "Mappa.h"
enum Tasti {
   TASTO_SOPRA, TASTO_SOTTO, STASTO_SINISTRA, TASTO_DESTRA
 };

void init();
void draw(string);

int main(int argc, char **argv){

  init();
  int w=1280;
  int h=1120;

  ALLEGRO_DISPLAY       *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;

  display=al_create_display(w, h);
  al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  timer=al_create_timer(1.0/60);

  event_queue = al_create_event_queue();

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_clear_to_color(al_map_rgb(0,0,0));
  al_flip_display();


  Giocatore * tommy= new Giocatore();
  tommy->carica_immagini();
  al_start_timer(timer);

  bool start=true; //indica che ho appena aperto il gioco
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
    if(start)
    {
      bool screen=0;
      bool redraw=true;
      ALLEGRO_BITMAP* schermata1= al_load_bitmap("./images/schermata_iniziale/schermata_iniziale_1.png");
      ALLEGRO_BITMAP* schermata2= al_load_bitmap("./images/schermata_iniziale/schermata_iniziale_2.png");
      while(start)
      {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
         {
           start=false;
           esc=true;
           al_destroy_bitmap(schermata1);
           al_destroy_bitmap(schermata2);
           break;
         }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
          switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ENTER:
            start=false;
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
        if( redraw && al_is_event_queue_empty(event_queue))
        {
        mappe[level].drawMappa();
        al_flip_display();
      }




      }
    }


  }



  al_rest(1);
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
