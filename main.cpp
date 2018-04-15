#include <iostream>
#include <string>
using namespace std;
#include "Giocatore.h"
#include "Mostro.h"
#include "Mappa.h"
#include "Colpo.h"
#include "Mostro_rosso.h"
#include "Mostro_Verde.h"
#include "Zucca.h"
#include <unistd.h>

const int ncolpi=10;
const int maxmostri=100;
const int levMax=10;

void init();
void draw(string);
//void mostraLivello(ALLEGRO_BITMAP*[],Mappa[],int&, int&);


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
  int contMostriColpiti=0;
  int indiceLanterna=0;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_TIMER *fantasma = NULL;
  ALLEGRO_TIMER *mostraliv=NULL;
  ALLEGRO_TIMER *passalivello=NULL;
  Colpo colpi[ncolpi]; //ARRAY DI COLPI
  Mappa mappe[levMax]; //ARRAY DI MAPPE
  Mostro *mostri[maxmostri]; //ARRAY DI MOSTRI
  Giocatore * tommy= new Giocatore(w,h); //DICHIARAZIONE GIOCATORE
  Zucca *zucca=new Zucca(0,0);
  bool main_screen=true;  //BOOLEANA CHE CONTROLLA LA PAGINA PRINCIPALE DEL GIOCO
  bool esc=false;       //BOOLEANA CHE CONTROLLA SE CLICCIAMO SULLA X
  bool mostrivivi=true;
  bool restart=false;  //BOOLEANA CHE SI ATTIVA QUANDO IL MOSTRO VIENE toccato
  bool gameover=false; //
  bool mostralivello=true;
  bool finitiSushi=false;
  ALLEGRO_BITMAP *schermate_livello[levMax];
  schermate_livello[0]=al_load_bitmap("./images/schermate/level1.png");
  schermate_livello[1]=al_load_bitmap("./images/schermate/level2.png");
  schermate_livello[2]=al_load_bitmap("./images/schermate/final_level.png");











  display=al_create_display(w, h);
  timer=al_create_timer(1.0/60);
  fantasma=al_create_timer(1.0);
  mostraliv=al_create_timer(1.0);
  passalivello=al_create_timer(1.0);
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
  mappe[1].caricaElementi("./images/objects/tile4.png");
  mappe[1].caricaMappa("./mappe/mappa2.txt");



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
        case 3:
        mostri[nMostri]=new Mostro_Verde();
        mostri[nMostri]->setX(i*92.08);
        mostri[nMostri]->setY(j*91.63);
        mostri[nMostri]->carica_immagini();
        nMostri++;
        break;
      }
    }
  }







  while(!esc)
  {
  // al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);

    //******************************************************//
    //WHILE UTILIZZATO PER ALTERNARE LE SCHERMATE PRINCIPALI//
    //******************************************************//

    if(main_screen) //SE MAIN SCREEN È TRUE SIAMO NELLA SCHERMATA PRINCIPALE
    {
      bool screen=0;
      bool redraw=true;
      ALLEGRO_BITMAP* schermata1= al_load_bitmap("./images/schermate/schermata_iniziale_1.png");
      ALLEGRO_BITMAP* schermata2= al_load_bitmap("./images/schermate/schermata_iniziale_2.png");



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

    //*********//
    //GAME OVER//
    //*********//

    if(gameover) //SE PERDIAMO TUTTE E 3 LE VITE
    {
      level=0;

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

           case ALLEGRO_KEY_ESCAPE:
           esc=true;
           al_destroy_bitmap(gameover1);
           al_destroy_bitmap(gameover2);

           break;
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
         al_start_timer(fantasma);
         al_start_timer(mostraliv);

         if(al_get_timer_count(mostraliv)>1)
         mostralivello=false;

         if(al_get_timer_count(fantasma)>10 && mostrivivi)
         {
          zucca->muoviZucca(tommy->getX(),tommy->getY());
         }

         if(contMostriColpiti>=3)
           {
             tommy->presaLanterna(mostri[indiceLanterna]->getX(),mostri[indiceLanterna]->getY());
           }




         if(restart ||(tommy->getToccato() && tommy->getCont1()>60)) //CONTROLLIAMO CHE RESTART NON SIA TRUE E CHE IL CONT1 ABBIA SUPERATO 60.
                                                                    //SE CONT1 SUPERA 60 VUOL DIRE CHE È STATA DISEGNATA L'INTERA ANIMAZIONE
         {
           al_set_timer_count(fantasma,0.0);
           al_set_timer_count(mostraliv,0.0);
           mostralivello=true;
           tommy->setX(w/2.0 - 15);         //SETTIAMO LE POS DEL GIOCATORE A QUELLE INIZIALI
           tommy->setY(h-30*4 -21*(4));
           tommy->setToccato(false);
           tommy->setCont1(0);              //SETTIAMO IL CONT1 A 0
           tommy->setSpostaMostro(false);
           tommy->setSparando(false);
           tommy->setAndando_destra(false);
           tommy->setAndando_sinistra(false);
           tommy->disattivaPotere();
           zucca->setX(0.0);
           zucca->setY(0.0);
           contMostriColpiti=0;
           restart=false;
           if(tommy->getVite()==0)          //CONTROLLIAMO CHE LE VITE NON SIANO 0 ALTRIMENTI GAMEOVER
           {
            gameover=true;
            al_set_timer_count(fantasma,0.0);
            al_set_timer_count(mostraliv,0.0);
            level=0;
           }

           for(int i=0;i<nMostri;i++)       //ELIMINIAMO I MOSTRI E CREIAMO NUOVI
           delete mostri[i];

           nMostri=0;

             for(int i=0;i<mappe[level].getMapSizeX();i++)
             {
               for(int j=0;j<mappe[level].getMapSizeY();j++)
               {
                 switch (mappe[level].getValore(i,j)) {
                   case 2:
                   mostri[nMostri]=new Mostro_rosso();
                   mostri[nMostri]->setX(i*92.08);
                   mostri[nMostri]->setY(j*91.63);
                   mostri[nMostri]->carica_immagini();
                   nMostri++;
                   break;

                   case 3:
                   mostri[nMostri]=new Mostro_Verde();
                   mostri[nMostri]->setX(i*92.08);
                   mostri[nMostri]->setY(j*91.63);
                   mostri[nMostri]->carica_immagini();
                   nMostri++;
                   break;
                    }
                  }
                }

                // ALLEGRO_TIMER *temp;
                // temp=al_create_timer(1.0);
                // al_start_timer(temp);
                //
                // while(al_get_timer_count(temp)!=1)
                // {
                //   al_clear_to_color(al_map_rgb(0,0,0));
                //  mappe[level].drawMappa();
                //   for(int i=0;i<nMostri;i++)
                //     if(mostri[i]->getVita())
                //     {
                //       mostri[i]->drawMostro();
                //     }
                //   al_draw_scaled_bitmap(schermate_livello[level], 0, 0, 256, 224, 0,0,w,h,0);
                //   al_flip_display();
                // }
                //
                // al_destroy_timer(temp);

                break;
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
          for(int i=0; i<ncolpi; i++) //AGGIORNIAMO LA POSIZIONE DEI COLPI
          {
            colpi[i].updateColpo();
          }

          for(int i=0;i<nMostri;i++) //FACCIAMO MUOVERE I MOSTRI
          {
            if(mostri[i]->getVita() && !mostralivello)
              mostri[i]->muovi();
          }

          float a=tommy->getX()/92.08;   //VARIABILI UTILIZZATE PER INTERAGIRE CON LA MAPPA
          float b=((tommy->getY()+90)/91.63);

          if(a<0)
            a=0;

          if(b<0)
            b=0;

          if(tommy->getToccato()==false && !mostralivello)//SE TOMMY NON E' STATO TOCCATO GLI PERMETTIAMO DI MUOVERSI
          tommy->muovi();


          /*if(mappe[level].getValore(a+1,b-1)==1 && tommy->getAndando_destra())//&& tommy->getSaltando())
          {
            tommy->setAndando_destra(false);
          }
          if(mappe[level].getValore(a-1,b-1)==1 && tommy->getAndando_sinistra())
          {
            tommy->setAndando_sinistra(false);
          }*/

          if(!tommy->getPotere()) //SE TOMMY HA IL POTERE NON HA GRAVITA'
          {
          if(tommy->getSaltando()==false)  //CONTROLLIAMO CHE IL PERSONAGGIO NON VADA DENTRO I MURETTI
          {
            if(tommy->getY()>400)
            {
              if((((int)tommy->getY()+30)/100)%2!=0 && !tommy->getPotere())
              {
                tommy->setCadendo(true);
                tommy->gravita();
              }
            }
            else if((((int)tommy->getY())/100)%2!=0)
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
        }






          for(int i=0; i<nMostri; i++) //CONTROLLIAMO SE QUALCHE MOSTRO O SE QUALCHE COLPO TOCCA IL PERSONAGGIO
          {
            if((!mostri[i]->getColpito() && !tommy->getToccato() && mostri[i]->getVita() && !mostri[i]->getcolpitoInnevato()&& !tommy->getPotere()))
              {
                tommy->controllaseToccato(mostri[i]->getX(), mostri[i]->getY());

                if(mostri[i]->getTipo()==1)
                tommy->controllaseToccato(mostri[i]->getxFuoco(), mostri[i]->getyFuoco());

                if(tommy->getToccato())
                {
                  //restart=true; //SE IL PERSONAGGIO VIENE TOCCATO SI ATTIVA IL RESTART E RICOMINCIA LA PARTITA
                  break;
                }
              }
          }

         for(int i=0;i<nMostri;i++) //CONTROLLIAMO SE TOMMY PRENDE IL SUSHI
         {
           if(mostri[i]->getSushi() && tommy->controllaseToccatoSushi(mostri[i]->getX(),mostri[i]->getY()))
           mostri[i]->setSushi(false);
         }

         if(!tommy->getToccato() && mostrivivi && !tommy->getPotere()) //CONTROLLIAMO SE TOMMY VIENE TOCCATO DALLA ZUCCA
         {
           tommy->controllaseToccato(zucca->getX(),zucca->getY());
         }


          for(int i=0; i<nMostri; i++)
          {
            if(mostri[i]->getVita())
            {
            float ma=mostri[i]->getX()/92.08; //VARIABILI CHE UTILIZZIAMO PER INTERAGIRE CON LA MAPPA PER LA GRAVITA'
            float mb=(mostri[i]->getY()/91.63)+1;
            if(ma<0)
              ma=0;
            if(mb<0)
              mb=0;

            if(mostri[i]->getTotInnevato())
            if(tommy->controllaTocco(mostri[i]->getX(), mostri[i]->getY(), mostri[i]->getTotInnevato(),mostri[i]->getColpito())) //CONTROLLIAMO SE QUALCHE MOSTRO E' TOT INNEVATO
                {
                  mostri[i]->muoviDaTommySeInnevato(tommy->getAndando_destra(), tommy->getAndando_sinistra(),  tommy->getSpostamento());
                }

                if(mostri[i]->getSaltando()==false) //CONTROLLIAMO CHE I MOSTRI NON VADANO DENTRO I MURETTI
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


              if(mappe[level].getValore(ma, mb)!=1 && mostri[i]->getSaltando()==false) //GRAVITA' DEI MOSTRI
              {
                mostri[i]->setCadendo(true);
                mostri[i]->gravita();
              }
              else
              {
                mostri[i]->setCadendo(false);
              }

              if(mostri[i]->getContPrimaDiSaltare()==0 && mappe[level].getValore(ma, mb-2)==1) //FA SALTARE I MOSTRI IN BASE AD UN NUMERO RANDOM
                mostri[i]->setSaltando(true);
            }

          }


           for(int i=0; i<nMostri; i++) //CONTROLLIAMO LA COLLISIONE TRA COLPI E MOSTRI
           {
             if(mostri[i]->getVita())
             {
                if(tommy->getPotere() && mostri[i]->collisioneProiettile(tommy->getX(),tommy->getY(),tommy->getFermoalternato()))
                {
                  mostri[i]->setcolpitoInnevato(true);
                  mostri[i]->setTotInnevato(true);
                }
                else
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
             if(mostri[i]->getVita() && !mostri[i]->getTotInnevato())
             {
               for(int j=0; j<nMostri; j++)
               {
                 if(mostri[j]->getVita())
                 {

                   // if(i!=j)
                   //cout<<i<<" "<<mostri[i]->getY()<<" - "<<j<<" "<<mostri[j]->getY()<<endl<<endl;
                   if(mostri[i]->controllaSeToccato(mostri[j]->getX(), mostri[j]->getY(), mostri[j]->getAndando_destra(), mostri[j]->getAndando_sinistra() && i!=j) ) //CONTROLLA LA COLLISIONE TRA MOSTRI
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

                    if(mostri[i]->getTotInnevato() || mostri[j]->getTotInnevato()) //CONTROLLA SE UN MOSTRO TOT INNEVATO TOCCA UN ALTRO MOSTRO
                    {
                      mostri[i]->setTotInnevato(true);
                      mostri[i]->setcolpitoInnevato(true);
                      mostri[j]->setTotInnevato(true);
                      mostri[j]->setcolpitoInnevato(true);
                      contMostriColpiti++;
                      if(contMostriColpiti==4)
                      {
                          indiceLanterna=i;
                          //contMostriColpiti=0;
                      }
                    }
                    //cout<<"cazzoooo"<<mostri[i]->getTotInnevato()<<" "<<mostri[j]->getTotInnevato()<<endl;
                  }
                }
              }
             }
           }
           mostrivivi=false;
           for(int i=0; i<nMostri; i++) //CONTROLLA SE TUTTI I MOSTRI SONO ANCORA VIVI PER PASSARE DI LIVELLO
           {
             if(mostri[i]->getVita())
              mostrivivi=true;
           }
           // cout<<tommy->getPotere()<<endl;
           if(!mostrivivi)
           {

             al_start_timer(passalivello);
             finitiSushi=true;
             for(int i=0; i<nMostri; i++)
             {
               if(mostri[i]->getSushi())
                finitiSushi=false;
             }
             if(finitiSushi)
             {
               level++;
               restart=true;
               al_set_timer_count(passalivello,0.0);
               al_stop_timer(passalivello);
               if(level>=2)
               gameover=true;
             }
             else if(al_get_timer_count(passalivello)>4 && !finitiSushi)
             {
               level++;
               restart=true;
               al_set_timer_count(passalivello,0.0);
               al_stop_timer(passalivello);
               if(level>=2)
               gameover=true;
             }
           }
         }


      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN && !restart && !mostralivello && !tommy->getToccato()) {
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
              tommy->setAndando_sopra(true);
              break;

            case ALLEGRO_KEY_DOWN:
              tommy->setAndando_sotto(true);
              break;

            case ALLEGRO_KEY_A:
              if(!tommy->getPotere())
              {
                tommy->setSparando(true);
                  for(int i=0;i<ncolpi && !colpi[i].fireColpo(tommy->getX(),tommy->getY(),tommy->getFermoalternato());i++);
              }
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

            case ALLEGRO_KEY_UP:
            tommy->setAndando_sopra(false);
            tommy->setFermo(true);
            break;

            case ALLEGRO_KEY_DOWN:
            tommy->setAndando_sotto(false);
            tommy->setFermo(true);
            break;
         }
      }

        if( redraw && al_is_event_queue_empty(event_queue))
        {


        mappe[level].drawMappa();
        if(mostralivello)
        {
          al_draw_scaled_bitmap(schermate_livello[level], 0, 0, 256, 224, 0,0,w,h,0);
        }

        for(int i=0;i<nMostri;i++)
          if(mostri[i]->getVita()|| mostri[i]->getSushi())
          {
            mostri[i]->drawMostro();
          }


        if(al_get_timer_count(fantasma)>10 && mostrivivi)
          zucca->drawZucca();


        if(contMostriColpiti>=3 && !tommy->getToccato() && !mostri[indiceLanterna]->getVita() && !tommy->getPotere())
        {
          tommy->drawLanterna(mostri[indiceLanterna]->getX(), mostri[indiceLanterna]->getY());
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

// void mostraLivello(ALLEGRO_BITMAP* schermate_livello[levMax],Mappa &mappe[levMax],int& level, int& nMostri)
// {
//   ALLEGRO_TIMER *temp;
//   temp=al_create_timer(1.0);
//   al_start_timer(temp);
//
//   while(al_get_timer_count(temp)!=1)
//   {
//     al_clear_to_color(al_map_rgb(0,0,0));
//    mappe[level].drawMappa();
//     for(int i=0;i<nMostri;i++)
//       if(mostri[i]->getVita())
//       {
//         mostri[i]->drawMostro();
//       }
//     al_draw_scaled_bitmap(schermate_livello[level], 0, 0, 256, 224, 0,0,w,h,0);
//     al_flip_display();
//   }
//   al_destroy_timer(temp);
// }
