#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#include "Giocatore.h"
#include "Mostro.h"
#include "Mappa.h"
#include "Colpo.h"
#include "Mostro_rosso.h"
#include "Mostro_Verde.h"
#include "Zucca.h"
#include "Boss.h"
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>


const int ncolpi=10;
const int maxmostri=100;
const int levMax=10;

void init();
void draw(string);
void drawBar(unsigned, int, ALLEGRO_FONT*, ALLEGRO_BITMAP*);
//void mostraLivello(ALLEGRO_BITMAP*[],Mappa[],int&, int&);


int main(int argc, char **argv){

  init();


  int w=12 *21; //252
  int h=11*21;//231

  ALLEGRO_DISPLAY       *display = NULL;
  //ALLEGRO_DISPLAY_MODE disp_data;

  // al_get_display_mode(al_get_num_display_modes()*0.30,&disp_data);
  //
  // int w1=disp_data.width;
  // int h1=disp_data.height;
  //
  // cout<<w1<<endl<<h1<<endl<<endl;

  // w=w1;
  // h=h1;




  ALLEGRO_TRANSFORM t;
	ALLEGRO_MONITOR_INFO data;

	al_get_monitor_info(al_get_num_video_adapters()-1, &data);

	int monitor_w = data.x2 - data.x1;
	int monitor_h = data.y2 - data.y1;

  //cout<<monitor_w<<" "<<monitor_h<<endl;
  monitor_w=1512;
  monitor_h=1386;
	float resize_x = monitor_w / static_cast<float>(w);
	float resize_y = monitor_h / static_cast<float>(h);
  cout<<monitor_w<<" "<<resize_x<<endl;
  cout<<monitor_w<<" "<<resize_x<<endl;



	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	display = al_create_display(monitor_w, monitor_h);

	al_identity_transform(&t);

	al_scale_transform(&t, resize_x, resize_y);

	al_use_transform(&t);



  unsigned level=0; //INDICE DELLA MAPPA PER CAMBIARE LIVELLO
  int nMostri=0; //NUMERO MOSTRI NELLA MAPPA
  int contMostriColpiti=0; //CONTATORE DEI MOSTRI COLPITI DALLA PALLA DI NEVE PER GESTIRE LA COMPARSA DELLA LANTERNA
  int indiceLanterna=0;   //INDICE DEL MOSTRO CHE TRASFORMATO IN PALLA DI NEVE HA COLPITO PIÙ MOSTRI.(GESTIONE POSIZIONI LANTERNA)
  int punti=0;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL; //TIMER PER GESTIONE DEGLI EVENTI
  ALLEGRO_TIMER *fantasma = NULL;  //TIMER PER GESTIRE LA COMPARSA DELLA ZUCCA DOPO UN TOT DI SECONDI
  ALLEGRO_TIMER *mostraliv=NULL;  //TIMER PER GESTIRE LA COMPARSA DEL LIVELLO NEL QUALE CI TROVIAMO
  ALLEGRO_TIMER *passalivello=NULL; //TIMER PER GESTIRE IL PASSAGGIO DA UN LIVELLO ALL'ALTRO. (TEMPO PER PRENDERE TUTTI I SUSHI)
  ALLEGRO_TIMER *creaMostriBoss=NULL;
  ALLEGRO_FONT *bar = al_load_ttf_font("Snow Bros.ttf",8,0 ); //FONT PER VISUALIZZARE LA DELLA VITA E I PUNTI
  ALLEGRO_BITMAP *bar_faccia= al_load_bitmap("./images/giocatore/elemento_barra.png");
  Colpo colpi[ncolpi]; //ARRAY DI COLPI
  Mappa mappe[levMax]; //ARRAY DI MAPPE
  Mostro *mostri[maxmostri]; //ARRAY DI MOSTRI
  Giocatore * tommy= new Giocatore(w,h); //DICHIARAZIONE GIOCATORE
  Zucca *zucca=new Zucca(0,0); //DICHIARAZIONE ZUCCA
  Boss *boss=new Boss();
  bool main_screen=true;  //BOOLEANA CHE CONTROLLA LA PAGINA PRINCIPALE DEL GIOCO
  bool esc=false;       //BOOLEANA CHE CONTROLLA SE CLICCHIAMO SULLA X
  bool mostrivivi=true; //BOOLEANA CHE CONTROLLA SE TUTTI I MOSTRI SONO MORTI
  bool restart=false;  //BOOLEANA CHE SI ATTIVA QUANDO IL GIOCATORE PERDE LE 3 VITE
  bool gameover=false; //BOOLEANA PER GESTIRE IL GAMEOVER
  bool mostralivello=true; //BOOLEANA PER GESTIRE IL TIMER CHE CI MOSTRA IL LIVELLO NEL QUALE CI TROVIAMO
  bool finitiSushi=false; //BOOLEANA CHE CI INDICA SE ABBIAMO PRESO TUTTI I SUSHI
  ALLEGRO_BITMAP *schermate_livello[levMax]; //ARRAY DI LIVELLI
  schermate_livello[0]=al_load_bitmap("./images/schermate/level1.png");
  schermate_livello[1]=al_load_bitmap("./images/schermate/level2.png");
  schermate_livello[2]=al_load_bitmap("./images/schermate/final_level.png");

  vector<Mostro*> mostriBoss;
  Mostro *mostroBoss;
  int mostroDaCreare;












  //display=al_create_display(w, h);
  timer=al_create_timer(1.0/60);
  fantasma=al_create_timer(1.0);
  mostraliv=al_create_timer(1.0);
  passalivello=al_create_timer(1.0);
  creaMostriBoss=al_create_timer(1.0);
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
  mappe[2].caricaElementi("./images/objects/tile3.png");
  mappe[2].caricaMappa("./mappe/mappa3.txt");


  for(int i=0;i<mappe[0].getMapSizeX();i++)  //CREIAMO I MOSTRI E LI INSERIAMO NELL'ARRAY IN BASE A DOVE SONO POSIZIONATI NELLA MAPPA
  {
    for(int j=0;j<mappe[0].getMapSizeY();j++)
    {
      switch (mappe[0].getValore(i,j)){
        case 2:
        mostri[nMostri]=new Mostro_rosso();
        mostri[nMostri]->setX(i*21);
        mostri[nMostri]->setY(j*21);
        mostri[nMostri]->carica_immagini();
        nMostri++;
        break;
        case 3:
        mostri[nMostri]=new Mostro_Verde();
        mostri[nMostri]->setX(i*21);
        mostri[nMostri]->setY(j*21);
        mostri[nMostri]->carica_immagini();
        nMostri++;
        break;
      }
    }
  }







  while(!esc)
  {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);

    //*******************************//
    //ALTERNANZA SCHERMATE PRINCIPALI//
    //*******************************//

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
          al_draw_bitmap(schermata1,  0,0, 0);
          al_flip_display();
          al_rest(0.5);
          screen=false;

        }
        else if(!screen && redraw && al_is_event_queue_empty(event_queue))
        {
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_bitmap(schermata2,  0,0, 0);
          al_flip_display();
          al_rest(0.5);
          screen=true;
        }
      }
    }

    //******************************//
    //ALTERNANZA SCHERMATE GAME OVER//
    //******************************//

    if(gameover) //SE PERDIAMO TUTTE E 3 LE VITE
    {

      if(level==2)
      {
        mostriBoss.clear();
        boss->restartBoss();
      }
      level=0;

      bool screen=0;
      bool redraw=true;
      ALLEGRO_BITMAP* gameover1= al_load_bitmap("./images/schermate/game_over1.png");
      ALLEGRO_BITMAP* gameover2= al_load_bitmap("./images/schermate/game_over2.png");
      while(gameover)
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
          al_draw_bitmap(gameover1,  0,0, 0);
          al_flip_display();
          al_rest(0.5);
          screen=true;

        }
        else if(screen && redraw && al_is_event_queue_empty(event_queue))
        {
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_bitmap(gameover2,  0,0, 0);
          al_flip_display();
          al_rest(0.5);
          screen=false;
        }
      }
    }


    //*****//
    //GIOCO//
    //*****//
    if(!esc && !gameover)
    {
      bool redraw=true;
      while(!esc && !gameover)
      {
         srand(time(0));
         al_start_timer(fantasma); //FACCIAMO PARTIRE IL TIMER PER LA COMPARSA DEL FANTASMA
         al_start_timer(mostraliv);//FACCIAMO PARTIRE IL TIMER CHE MI MOSTRA IL LIVELLO NEL QUALE CI TROVIAMO

         if(!al_get_timer_started(creaMostriBoss)&&level==2)
         al_start_timer(creaMostriBoss);



         if(al_get_timer_count(mostraliv)>1) //SE IL LIVELLO NEL QUALE CI TROVIAMO È STATO MOSTRATO PER PIÙ DI 1 SECONDO, NON LO MOSTRARE PIÙ
         mostralivello=false;

         if(al_get_timer_count(fantasma)>10 && mostrivivi && level!=2) //SE CI SONO ANCORA MOSTRI VIVI E SONO PASSATI 30 SECONDI FACCIAMO COMPARIRE LA ZUCCA
         {
          zucca->muoviZucca(tommy->getX(),tommy->getY());
         }

         if(contMostriColpiti>=1) //CONTROLLIAMO SE TOMMY SI TROVA NELLA STESSA POSIZIONE DELLA LANTERNA
           {
             tommy->presaLanterna(mostri[indiceLanterna]->getX(),mostri[indiceLanterna]->getY());
           }

         if(restart ||(tommy->getToccato() && tommy->getCont1()>60)) //CONTROLLIAMO CHE RESTART NON SIA TRUE E CHE IL CONT1 ABBIA SUPERATO 60.
                                                                    //SE CONT1 SUPERA 60 VUOL DIRE CHE È STATA DISEGNATA L'INTERA ANIMAZIONE
         {
           al_set_timer_count(fantasma,0.0);  //SETTIAMO I TIMER A 0
           al_set_timer_count(mostraliv,0.0);
           mostralivello=true;                //BOOLEANA CHE SI RIATTIVA PER MOSTRARE NUOVAMENTE IL LIVELLO
           tommy->setX(w/2.0 - 15);           //SETTIAMO LE IMPOSTAZIONI DI TOMMY A QUELLE INIZIALI
           tommy->setY(h-(21*2)-15);
           tommy->setToccato(false);
           tommy->setCont1(0);
           tommy->setSpostaMostro(false);
           tommy->setSparando(false);
           tommy->setAndando_destra(false);
           tommy->setAndando_sinistra(false);
           tommy->disattivaPotere();
           zucca->setX(0.0);
           zucca->setY(0.0);
           contMostriColpiti=0;
           restart=false;
           if(level==2)
           {
             // for(int i=0; i<mostriBoss.size(); i++)
             //  delete mostri[i];
            mostriBoss.clear();
            al_set_timer_count(creaMostriBoss,0.0);
            boss->restartBoss();
           }

           if(tommy->getVite()==0)          //CONTROLLIAMO CHE LE VITE NON SIANO 0 ALTRIMENTI GAMEOVER
           {
            gameover=true;
            al_set_timer_count(fantasma,0.0);
            al_set_timer_count(mostraliv,0.0);
            level=0;
           }

           for(int i=0;i<nMostri;i++)       //ELIMINIAMO I MOSTRI E CREIAMO NUOVI PER EVITARE DI IMPOSTARE I SETTAGGI A QUELLI INIZIALI
           delete mostri[i];

           nMostri=0;
            if(level!=2)
            {
             for(int i=0;i<mappe[level].getMapSizeX();i++)
             {
               for(int j=0;j<mappe[level].getMapSizeY();j++)
               {
                 switch (mappe[level].getValore(i,j)) {
                   case 2:
                   mostri[nMostri]=new Mostro_rosso();
                   mostri[nMostri]->setX(i*21);
                   mostri[nMostri]->setY(j*21);
                   mostri[nMostri]->carica_immagini();
                   nMostri++;
                   break;

                   case 3:
                   mostri[nMostri]=new Mostro_Verde();
                   mostri[nMostri]->setX(i*21);
                   mostri[nMostri]->setY(j*21);
                   mostri[nMostri]->carica_immagini();
                   nMostri++;
                   break;
                    }
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
                //   al_draw_bitmap(schermate_livello[level],  0,0, 0);
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


          if(level==2 && !mostralivello)  //FACCIAMO MUOVERE I MOSTRI DEL BOSS SE NON SONO MORTI E SE C'È LA SCHERMATA DEL LIVELLO
          {
            boss->gestisciBoss();
            for(int i=0;i<mostriBoss.size();i++)
              if(mostriBoss[i]->getVita() && !mostralivello)
                mostriBoss[i]->muovi();

            if(al_get_timer_count(creaMostriBoss)==2 && boss->getVita()) //OGNI 5 SEC VIENE CREATO UN NUOVO MOSTRO DEL BOSS
            {
              al_set_timer_count(creaMostriBoss,0.0);
              mostroDaCreare=rand()%2+1;

              if(mostroDaCreare==1)
              {
                //cout<<"cazzo"<<endl<<endl;
                mostroBoss=new Mostro_rosso();
                mostroBoss->setX(100);
                mostroBoss->setY(5);
                mostriBoss.push_back(mostroBoss);
                mostriBoss.back()->carica_immagini();
              }
              else if(mostroDaCreare==2)
              {
                //cout<<"figaaa"<<endl<<endl;
                mostroBoss=new Mostro_Verde();
                mostroBoss->setX(100);
                mostroBoss->setY(5);
                mostriBoss.push_back(mostroBoss);
                mostriBoss.back()->carica_immagini();

              }
            }
          }




          float a=(tommy->getX()+15)/21;   //VARIABILI UTILIZZATE PER INTERAGIRE CON IL FILE DI TESTO DELLA MAPPA E GESTIRE LA GRAVITÀ
          float b=((tommy->getY()+28)/21);

          if(a<0)
            a=0;

          if(b<0)
            b=0;
          //cout<<a<< " - "<<b<<endl;

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
            /*if(tommy->getSaltando()==false)  //CONTROLLIAMO CHE IL PERSONAGGIO NON VADA DENTRO I MURETTI
            {
              if(tommy->getY()>231)
              {
                if((((int)tommy->getY())/100)%2!=0 && !tommy->getPotere())
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
            */
            if((mappe[level].getValore(a, b)!=1 && tommy->getSaltando()==false)) //GESTIAMO LA GRAVITA' DEL PERSONAGGIO
            {
            tommy->setCadendo(true);
            tommy->gravita();
            }
            else
            {
            tommy->setCadendo(false);
            tommy->setFermo(true);
            }
          }






         for(int i=0; i<nMostri; i++)
         {
            if(mostri[i]->getVita() && !mostralivello) //FACCIAMO MUOVERE I MOSTRI SE NON SONO MORTI E SE C'È LA SCHERMATA DEL LIVELLO
              mostri[i]->muovi();


            if((!mostri[i]->getColpito() && !tommy->getToccato() && mostri[i]->getVita() && !mostri[i]->getcolpitoInnevato()&& !tommy->getPotere()))//CONTROLLIAMO SE QUALCHE MOSTRO O SE QUALCHE COLPO TOCCA IL PERSONAGGIO
              {
                tommy->controllaseToccato(mostri[i]->getX(), mostri[i]->getY());

                if(mostri[i]->getTipo()==1)
                tommy->controllaseToccato(mostri[i]->getxFuoco(), mostri[i]->getyFuoco());

                if(tommy->getToccato())
                {
                  break;
                }
              }

            if(mostri[i]->getSushi() && tommy->controllaseToccatoSushi(mostri[i]->getX(),mostri[i]->getY()))//CONTROLLIAMO SE TOMMY PRENDE IL SUSHI
              mostri[i]->setSushi(false);


            if(mostri[i]->getVita())
              {
              float ma=(mostri[i]->getX()+9)/21; //VARIABILI CHE UTILIZZIAMO PER INTERAGIRE CON LA MAPPA PER LA GRAVITA'
              float mb=((mostri[i]->getY()+0.2)/21)+1;
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
                  /*{
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
                  }*/

                  //cout<<mappe[level].getValore(ma, mb)<<endl;
                if(mappe[level].getValore(ma, mb)!=1) //GRAVITA' DEI MOSTRI
                {
                  if(mostri[i]->getSaltando()==false)
                  {
                    mostri[i]->setCadendo(true);
                    mostri[i]->gravita();
                  }
                }

                else
                {
                  mostri[i]->setCadendo(false);
                }

                if(mostri[i]->getContPrimaDiSaltare()==0 && mappe[level].getValore(ma, mb-2)==1) //FA SALTARE I MOSTRI IN BASE AD UN NUMERO RANDOM
                  mostri[i]->setSaltando(true);
              }









         }

         if(level==2)  //CONTROLLIAMO SE I MOSTRI DEL BOSS O QUALCHE COLPO TOCCA TOMMY
         {
           for(int i=0;i<mostriBoss.size();i++)
           {
             if((!mostriBoss[i]->getColpito() && !tommy->getToccato() && mostriBoss[i]->getVita() && !mostriBoss[i]->getcolpitoInnevato()&& !tommy->getPotere()))
               {
                 tommy->controllaseToccato(mostriBoss[i]->getX(), mostriBoss[i]->getY());

                 if(mostriBoss[i]->getTipo()==1)
                  tommy->controllaseToccato(mostriBoss[i]->getxFuoco(), mostriBoss[i]->getyFuoco());

                 if(tommy->getToccato())
                 {
                   break;
                 }
               }
           }

           tommy->controllaseToccato(boss->getxFuoco(), boss->getyFuoco());
         }


         for(int i=0;i<mostriBoss.size();i++) //CONTROLLIAMO SE TOMMY PRENDE IL SUSHI DEI MOSTRI DEL BOSS
         {
           if(mostriBoss[i]->getSushi() && tommy->controllaseToccatoSushi(mostriBoss[i]->getX(),mostriBoss[i]->getY()))
           mostriBoss[i]->setSushi(false);
         }

         if(!tommy->getToccato() && mostrivivi && !tommy->getPotere()) //CONTROLLIAMO SE TOMMY VIENE TOCCATO DALLA ZUCCA
         {
           tommy->controllaseToccato(zucca->getX(),zucca->getY());
         }

         if(level==2) //GRAVITA DEL MOSTRO BOSS
         {
           float ma=boss->getX()/21; //VARIABILI CHE UTILIZZIAMO PER INTERAGIRE CON LA MAPPA PER LA GRAVITA'
           float mb=((boss->getY()+10)/21)+3;
           if(ma<0)
             ma=0;
           if(mb<0)
             mb=0;
          if(mappe[level].getValore(ma, mb)!=1 && boss->getSaltando()==false) //GRAVITA' DEI MOSTRI
             {
               boss->setCadendo(true);
               boss->gravita();
             }
          else
           {
               boss->setCadendo(false);
           }
         }

          if(level==2)
          {
              for(int i=0; i<mostriBoss.size(); i++) //CONTROLLIAMO LA GRAVITÀ DEI MOSTRI DEL BOSS E CONTROLLIAMO CHE NON VADANO DENTRO I MURETTI
                {
                    if(mostriBoss[i]->getVita())
                      {
                        float ma=(mostriBoss[i]->getX()-9)/21; //VARIABILI CHE UTILIZZIAMO PER INTERAGIRE CON LA MAPPA PER LA GRAVITA'
                        float mb=(mostriBoss[i]->getY()/21)+1;
                          if(ma<0)
                            ma=0;
                          if(mb<0)
                            mb=0;

                         if(mostriBoss[i]->getTotInnevato())
                            if(tommy->controllaTocco(mostriBoss[i]->getX(), mostriBoss[i]->getY(), mostriBoss[i]->getTotInnevato(),mostriBoss[i]->getColpito())) //CONTROLLIAMO SE QUALCHE MOSTRO E' TOT INNEVATO
                              {
                                mostriBoss[i]->muoviDaTommySeInnevato(tommy->getAndando_destra(), tommy->getAndando_sinistra(),  tommy->getSpostamento());
                              }

                          /*if(mostriBoss[i]->getSaltando()==false) //CONTROLLIAMO CHE I MOSTRI NON VADANO DENTRO I MURETTI
                          {
                            if(mostriBoss[i]->getY()>400)
                            {
                              if((((int)mostriBoss[i]->getY()+30)/100)%2!=0)
                              {
                                mostriBoss[i]->setCadendo(true);
                                mostriBoss[i]->gravita();
                              }
                            }
                            else if((((int)mostriBoss[i]->getY())/100)%2!=0)
                            {
                              mostriBoss[i]->setCadendo(true);
                              mostriBoss[i]->gravita();
                            }
                          }*/


                    if(mappe[level].getValore(ma, mb)!=1 && mostriBoss[i]->getSaltando()==false) //GRAVITA' DEI MOSTRI
                    {
                      mostriBoss[i]->setCadendo(true);
                      mostriBoss[i]->gravita();
                    }
                    else
                    {
                      mostriBoss[i]->setCadendo(false);
                    }

                    if(mostriBoss[i]->getContPrimaDiSaltare()==0 && mappe[level].getValore(ma, mb-2)==1) //FA SALTARE I MOSTRI IN BASE AD UN NUMERO RANDOM
                      mostriBoss[i]->setSaltando(true);
                    }


                    if(mostriBoss[i]->getVita()) //CONTROLLIAMO LA COLLISIONE TRA COLPI E MOSTRI DEL BOSS
                    {
                       if(tommy->getPotere() && mostriBoss[i]->collisioneProiettile(tommy->getX(),tommy->getY(),tommy->getFermoalternato()))
                       {
                         mostriBoss[i]->setcolpitoInnevato(true);
                         mostriBoss[i]->setTotInnevato(true);
                       }
                       else
                       for(int j=0; j<ncolpi; j++)
                       {
                           if(colpi[j].getVita())
                             if(mostriBoss[i]->collisioneProiettile(colpi[j].getX(), colpi[j].getY(),tommy->getFermoalternato()))
                               colpi[j].setVita(false);
                       }
                    }

                      if(mostriBoss[i]->getTotInnevato() && mostriBoss[i]->getcolpitoInnevato()) //CONTROLLIAMO SE UN MOSTRO TOTALMENTE INNEVATO COLPISCE IL BOSS
                        if(boss->controllaSeToccato(mostriBoss[i]->getX(),mostriBoss[i]->getY(),1))
                          mostriBoss[i]->sconfitto();


                       for(int j=0; j<ncolpi; j++) //CONTROLLIAMO SE I COLPI DI TOMMY COLPISCONO IL BOSS
                       {
                           if(colpi[j].getVita())
                             if(boss->controllaSeToccato(colpi[j].getX(),colpi[j].getY(),0))
                               colpi[j].setVita(false);
                       }
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




           for(int i=0; i<nMostri; i++) //COLLISIONE TRA MOSTRI
           {
             if(mostri[i]->getVita() && !mostri[i]->getTotInnevato())
             {
               for(int j=0; j<nMostri; j++)
               {
                 if(mostri[j]->getVita())
                 {

                   // if(i!=j)
                   //cout<<i<<" "<<mostri[i]->getY()<<" - "<<j<<" "<<mostri[j]->getY()<<endl<<endl;
                   if(mostri[i]->controllaSeToccato(mostri[j]->getX(), mostri[j]->getY(), mostri[j]->getAndando_destra(), mostri[j]->getAndando_sinistra() && i!=j)) //CONTROLLA LA COLLISIONE TRA MOSTRI ED INVERTE LO SPOSTAMENTO
                   {
                     if(mostri[i]->getAndando_destra())
                     {
                       mostri[i]->setAndando_destra(false);
                       mostri[i]->setAndando_sinistra(true);

                       mostri[j]->setAndando_destra(true);
                       mostri[j]->setAndando_sinistra(false);

                       mostri[i]->setX(mostri[i]->getX()-7);
                       mostri[j]->setX(mostri[j]->getX()+7);
                     }
                     else if(mostri[j]->getAndando_destra())
                     {
                       mostri[i]->setAndando_destra(true);
                       mostri[i]->setAndando_sinistra(false);

                       mostri[j]->setAndando_destra(false);
                       mostri[j]->setAndando_sinistra(true);

                       mostri[i]->setX(mostri[i]->getX()+7);
                       mostri[j]->setX(mostri[j]->getX()-7);

                    }

                    if(mostri[i]->getTotInnevato() || mostri[j]->getTotInnevato()) //CONTROLLA SE UN MOSTRO TOT INNEVATO TOCCA UN ALTRO MOSTRO // NON FUNZIONA
                    {
                      mostri[i]->setTotInnevato(true);
                      mostri[i]->setcolpitoInnevato(true);
                      mostri[j]->setTotInnevato(true);
                      mostri[j]->setcolpitoInnevato(true);
                      contMostriColpiti++;
                      if(contMostriColpiti==1)
                      {
                          indiceLanterna=i;
                      }
                    }
                  }
                }
              }
             }
           }

          if(level==2)
           {
             for(int i=0; i<mostriBoss.size(); i++) //COLLISIONE TRA MOSTRIBOSS
             {
             if(mostriBoss[i]->getVita() && !mostriBoss[i]->getTotInnevato())
             {
               for(int j=0; j<mostriBoss.size(); j++)
               {
                 if(mostriBoss[j]->getVita())
                 {

                   // if(i!=j)
                   //cout<<i<<" "<<mostriBoss[i]->getY()<<" - "<<j<<" "<<mostriBoss[j]->getY()<<endl<<endl;
                   if(mostriBoss[i]->controllaSeToccato(mostriBoss[j]->getX(), mostriBoss[j]->getY(), mostriBoss[j]->getAndando_destra(), mostriBoss[j]->getAndando_sinistra()) && i!=j) //CONTROLLA LA COLLISIONE TRA MOSTRI ED INVERTE LO SPOSTAMENTO //MODIFICARE LA FUNZIONE
                   {
                     if(mostriBoss[i]->getAndando_destra())
                     {
                       mostriBoss[i]->setAndando_destra(false);
                       mostriBoss[i]->setAndando_sinistra(true);

                       mostriBoss[j]->setAndando_destra(true);
                       mostriBoss[j]->setAndando_sinistra(false);

                       mostriBoss[i]->setX(mostriBoss[i]->getX()-7);
                       mostriBoss[j]->setX(mostriBoss[j]->getX()+7);

                       mostriBoss[i]->diminuisciContPrimaDiSaltare();
                       mostriBoss[j]->diminuisciContPrimaDiSaltare();
                     }
                     else if(mostriBoss[j]->getAndando_destra())
                     {
                       mostriBoss[i]->setAndando_destra(true);
                       mostriBoss[i]->setAndando_sinistra(false);

                       mostriBoss[j]->setAndando_destra(false);
                       mostriBoss[j]->setAndando_sinistra(true);

                       mostriBoss[i]->setX(mostriBoss[i]->getX()+7);
                       mostriBoss[j]->setX(mostriBoss[j]->getX()-7);

                      mostriBoss[i]->diminuisciContPrimaDiSaltare();
                      mostriBoss[j]->diminuisciContPrimaDiSaltare();
                    }

                    if(mostriBoss[j]->controllaSeToccato(boss->getX(), boss->getY(), false, false))
                    {
                      if(mostriBoss[j]->getAndando_destra())
                      {


                        mostriBoss[j]->setAndando_destra(false);
                        mostriBoss[j]->setAndando_sinistra(true);

                        mostriBoss[j]->setX(mostriBoss[j]->getX()-7);

                        mostriBoss[j]->diminuisciContPrimaDiSaltare();
                     }

                    }


                    if(mostriBoss[i]->getTotInnevato() || mostriBoss[j]->getTotInnevato()) //CONTROLLA SE UN MOSTRO TOT INNEVATO TOCCA UN ALTRO MOSTRO
                    {
                      mostriBoss[i]->setTotInnevato(true);
                      mostriBoss[i]->setcolpitoInnevato(true);
                      mostriBoss[j]->setTotInnevato(true);
                      mostriBoss[j]->setcolpitoInnevato(true);
                      // contMostriColpiti++;
                      // if(contMostriColpiti==1)
                      // {
                      //     indiceLanterna=i;
                      // }
                    }
                  }
                }
              }
             }
           }
           }




           if(level!=2)
           {
             mostrivivi=false;
           for(int i=0; i<nMostri; i++) //CONTROLLA SE TUTTI I MOSTRI SONO ANCORA VIVI PER PASSARE DI LIVELLO
           {
             if(mostri[i]->getVita())
              mostrivivi=true;
           }
           // cout<<tommy->getPotere()<<endl;
           if(!mostrivivi && level!=2)
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
               if(level>=3)
               gameover=true;
             }
             else if(al_get_timer_count(passalivello)>4 && !finitiSushi)
             {
               level++;
               restart=true;
               al_set_timer_count(passalivello,0.0);
               al_stop_timer(passalivello);
               if(level>=3)
                gameover=true;
             }
           }
         }
         else if(level==2)
         {
           if(!boss->getVita())
            mostriBoss.clear();
           if(boss->getTimerCaduta()>=50)
            gameover=true; //FARE LA SCHERMATA WIN
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


        for(int i=0;i<nMostri;i++)
          if(mostri[i]->getVita()|| mostri[i]->getSushi())
          {
            mostri[i]->drawMostro();
          }


        if(al_get_timer_count(fantasma)>10 && mostrivivi)
          zucca->drawZucca();


        if(contMostriColpiti>=1 && !tommy->getToccato() && !mostri[indiceLanterna]->getVita() && !tommy->getPotere())
        {
          tommy->drawLanterna(mostri[indiceLanterna]->getX(), mostri[indiceLanterna]->getY());
        }

        if(level==2)
        {
          boss->drawBoss();

          for(int i=0;i<mostriBoss.size();i++)
           mostriBoss[i]->drawMostro();
        }



        tommy->drawPersonaggio();

        for(int i=0;i<ncolpi;i++)
        {
          colpi[i].drawColpo();
        }

        drawBar(tommy->getVite(), punti, bar, bar_faccia);
        if(mostralivello)
        {
          al_draw_bitmap(schermate_livello[level],  0,0, 0);
        }

        al_flip_display();
        }
      }
    }
  }

  al_destroy_bitmap(bar_faccia);
  al_destroy_font(bar);
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
  al_init_font_addon();
  al_init_ttf_addon();
}

void drawBar(unsigned vite, int punti, ALLEGRO_FONT * bar, ALLEGRO_BITMAP * faccia)
{
  string vit=to_string(vite);
  char * v= new char [vit.length()+1];
  strcpy(v, vit.c_str());

  string punt=to_string(punti);
  char * p= new char [punt.length()+1];
  strcpy(p, punt.c_str());

  al_draw_scaled_bitmap(faccia,  0, 0, al_get_bitmap_width(faccia),  al_get_bitmap_height(faccia), 72, 0, al_get_bitmap_width(faccia)-4, al_get_bitmap_height(faccia)-5, 0);
  al_draw_text(bar, al_map_rgb(255,242,0), 82, 2,ALLEGRO_ALIGN_LEFT, "X");
  al_draw_text(bar, al_map_rgb(255,242,0), 92, 2,ALLEGRO_ALIGN_LEFT, v);

  al_draw_text(bar, al_map_rgb(255,242,0), 110, 2,ALLEGRO_ALIGN_LEFT, "HISCORE");
  al_draw_text(bar, al_map_rgb(255,242,0), 175, 2,ALLEGRO_ALIGN_LEFT, p);





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
//     al_draw_bitmap(schermate_livello[level],  0,0, 0);
//     al_flip_display();
//   }
//   al_destroy_timer(temp);
// }
