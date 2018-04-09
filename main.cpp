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

  ALLEGRO_DISPLAY       *display = NULL;
  /*

  ALLEGRO_TRANSFORM t;
	ALLEGRO_MONITOR_INFO data;

	al_get_monitor_info(0, &data);

	int monitor_w = data.x2 - data.x1;
	int monitor_h = data.y2 - data.y1;

	float resize_x = monitor_w / static_cast<float>(w);
	float resize_y = monitor_h / static_cast<float>(h);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	display = al_create_display(monitor_w, monitor_h);

	al_identity_transform(&t);

	al_scale_transform(&t, resize_x, resize_y);

	al_use_transform(&t);


  */
  unsigned level=0; //INDICE DELLA MAPPA PER CAMBIARE LIVELLO
  int nMostri=0; //NUMERO MOSTRI NELLA MAPPA
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  Colpo colpi[ncolpi]; //ARRAY DI COLPI
  Mappa mappe[2]; //ARRAY DI MAPPE
  Mostro *mostri[maxmostri]; //ARRAY DI MOSTRI
  Giocatore * tommy= new Giocatore(w,h); //DICHIARAZIONE GIOCATORE
  bool main_screen=true;  //BOOLEANA CHE CONTROLLA LA PAGINA PRINCIPALE DEL GIOCO
  bool esc=false;       //BOOLEANA CHE CONTROLLA SE CLICCIAMO SULLA X
  bool mostrivivi=true;
  bool restart=false;  //BOOLEANA CHE SI ATTIVA QUANDO IL MOSTRO VIENE toccato
  bool gameover=false; //









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



  for(int i=0;i<mappe[0].getMapSizeX();i++)  //CREIAMO UN ARRAY DI MOSTRI
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

    if(main_screen) //SE MAIN SCREEN È TRUE SIAMO NELLA SCHERMATA PRINCIPALE
    {
      bool screen=0;
      bool redraw=true;
      ALLEGRO_BITMAP* schermata1= al_load_bitmap("./images/schermate/schermata_iniziale_1.png");
      ALLEGRO_BITMAP* schermata2= al_load_bitmap("./images/schermate/schermata_iniziale_2.png");



      while(main_screen) //WHILE UTILIZZATO PER ALTERNARE LE SCHERMATE PRINCIPALI
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

    if(gameover) //SE PERDIAMO TUTTE E 3 LE VITE
    {
      bool screen=0;
      bool redraw=true;
      ALLEGRO_BITMAP* gameover1= al_load_bitmap("./images/schermate/game_over1.png");
      ALLEGRO_BITMAP* gameover2= al_load_bitmap("./images/schermate/game_over2.png");
      while(gameover)   //WHILE UTILIZZATO PER ALTERNARE LA SCHERMATA DI GAMEOVER
      {

        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
         {
           esc=true;
           al_destroy_bitmap(gameover1);
           al_destroy_bitmap(gameover2);
           break;
         }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
          switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ENTER:
            gameover=false;
            redraw=false;
            tommy->setVite(3);
            al_destroy_bitmap(gameover1);
            al_destroy_bitmap(gameover2);
            break;

            // case ALLEGRO_KEY_C:
            // esc=true;
            // al_destroy_bitmap(gameover1);
            // al_destroy_bitmap(gameover2);
            //
            // break;
          }
        if(!screen && redraw && al_is_event_queue_empty(event_queue))
        {
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_scaled_bitmap(gameover1, 0, 0, 256, 224, 0,0,w,h,0);
          al_flip_display();
          al_rest(0.5);
          screen=true;

        }
        else if(screen && redraw && al_is_event_queue_empty(event_queue))
        {
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_scaled_bitmap(gameover2, 0, 0, 256, 224, 0,0,w,h,0);
          al_flip_display();
          al_rest(0.5);
          screen=false;
        }
      }

    }


    if(!esc && !gameover) //
    {
      bool redraw=true;
      while(!esc && !gameover)
      {
         if(restart && tommy->getCont1()>60) //CONTROLLIAMO CHE RESTART NON SIA TRUE E CHE IL CONT1 ABBIA SUPERATO 60.
                                             //SE CONT1 SUPERA 60 VUOL DIRE CHE È STATA DISEGNATA L'INTERA ANIMAZIONE
         {
           tommy->setX(w/2.0 - 15);         //SETTIAMO LE POS DEL GIOCATORE A QUELLE INIZIALI
           tommy->setY(h-30*4 -21*(4));
           tommy->setToccato(false);
           tommy->setCont1(0);              //SETTIAMO IL CONT1 A 0
           restart=false;
           if(tommy->getVite()==0)          //CONTROLLIAMO CHE LE VITE NON SIANO 0
           {
            gameover=true;
            break;
           }

           for(int i=0;i<nMostri;i++)
           delete mostri[i];

           nMostri=0;

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

            }




        al_clear_to_color(al_map_rgb(0,0,0));
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
         {
           esc=true;
           break;
         }

         else if(ev.type == ALLEGRO_EVENT_TIMER)
         {
           //aggiorno la posizione del giocatore


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
          float b=((tommy->getY()+90)/91.63);

          if(a<0)
            a=0;

          if(b<0)
            b=0;
          if(tommy->getToccato()==false)
          tommy->muovi();


          /*if(mappe[level].getValore(a+1,b-1)==1 && tommy->getAndando_destra())//&& tommy->getSaltando())
          {
            tommy->setAndando_destra(false);
          }
          if(mappe[level].getValore(a-1,b-1)==1 && tommy->getAndando_sinistra())
          {
            tommy->setAndando_sinistra(false);
          }*/


          if(tommy->getSaltando()==false)  //CONTROLLIAMO CHE IL PERSONAGGIO NON VADA DENTRO I MURETTI
          {
            if(tommy->getY()>400)
            {
              if((((int)tommy->getY()+30)/100)%2!=0)
              {
                tommy->setCadendo(true);
                tommy->gravita();
              }
            }
            else if((((int)tommy->getY()+5)/100)%2!=0)
            {
              tommy->setCadendo(true);
              tommy->gravita();
            }
          }

          if((mappe[level].getValore(a, b)!=1 && tommy->getSaltando()==false)) //GESTIAMO LA GRAVITA' DEL PERSONAGGIO
          {
            tommy->setCadendo(true);
            tommy->gravita();
            //cout<<tommy->getX()<<"   "<<tommy->getY()<<"   "<<((int)tommy->getY()+5)/100<<endl<<endl;
          }
          else
          {
            tommy->setCadendo(false);
            tommy->setFermo(true);
          }






          for(int i=0; i<nMostri; i++)
          {
            if(!mostri[i]->getColpito() && !tommy->getToccato())
              {
                tommy->controllaseToccato(mostri[i]->getX(), mostri[i]->getY());
                if(tommy->getToccato())
                {
                  restart=true;
                  break;
                }
              }
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

            if(tommy->controllaTocco(mostri[i]->getX(), mostri[i]->getY(), mostri[i]->getTotInnevato(),mostri[i]->getColpito())) //tommy sposta i
              //mostri solo se sono totalmente innevati
                {
                  mostri[i]->muoviDaTommySeInnevato(tommy->getAndando_destra(), tommy->getAndando_sinistra(),  tommy->getSpostamento());
                }






                if(mostri[i]->getSaltando()==false)
                {
                  if(mostri[i]->getY()>400)
                  {
                    if((((int)mostri[i]->getY()+30)/100)%2!=0)
                    {
                      mostri[i]->setCadendo(true);
                      mostri[i]->gravita();
                    }
                  }
                  else if((((int)mostri[i]->getY())/100)%2!=0)
                  {
                    mostri[i]->setCadendo(true);
                    mostri[i]->gravita();
                  }
                }


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
                  if(mostri[i]->collisioneProiettile(colpi[j].getX(), colpi[j].getY(),tommy->getFermoalternato()))
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


      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN && !restart) {
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

        if(ev.type == ALLEGRO_EVENT_KEY_UP || restart) {
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
