#include "Mostro_Verde.h"

Mostro_Verde::Mostro_Verde()
{
    Mostro();
    saltando =false;
    // andando_destra=true;
    // andando_sinistra=false;
    colpito=false;
    nColpito=0;
    al_start_timer(congelo);
    contPrimaDiSparare=100;
    sparaFuoco=false;
    lunghezzaFuoco=50;
    xFuoco=-100;
    yFuoco=-100;
    tipo=1;

}

Mostro_Verde::~Mostro_Verde()
{
    al_destroy_bitmap(innevando1);
    al_destroy_bitmap(innevando2);
    al_destroy_bitmap(innevando3);
    al_destroy_bitmap(palladineve1);
    al_destroy_bitmap(palladineve2);

    al_destroy_bitmap(verso_sinistra1);
    al_destroy_bitmap(verso_sinistra2);
    al_destroy_bitmap(colpito_sinistra1);
    al_destroy_bitmap(colpito_sinistra2);
    al_destroy_bitmap(verso_destra1);
    al_destroy_bitmap(verso_destra2);
    al_destroy_bitmap(colpito_destra1);
    al_destroy_bitmap(colpito_destra2);
    al_destroy_bitmap(salta);
}

void Mostro_Verde::setSparaFuoco(bool l)
{
    sparaFuoco=l;
}

bool Mostro_Verde::getSparaFuoco()
{
    return sparaFuoco;
}

Mostro_Verde::Mostro_Verde(float x1, float y2)
{
    Mostro(x1,y2);
    saltando=false;
    andando_destra=true;
    andando_sinistra=false;
    colpito=false;
    nColpito=0;
    tipo=1;
    sparaFuoco=false;

}


void Mostro_Verde::carica_immagini()
{
    verso_sinistra1=al_load_bitmap("./images/mostro_verde/sinistra1.png");
    verso_sinistra2=al_load_bitmap("./images/mostro_verde/sinistra2.png");
    colpito_sinistra1=al_load_bitmap("./images/mostro_verde/colpito1_sx.png");
    colpito_sinistra2=al_load_bitmap("./images/mostro_verde/colpito2_sx.png");

    verso_destra1=al_load_bitmap("./images/mostro_verde/destra1.png");
    verso_destra2=al_load_bitmap("./images/mostro_verde/destra2.png");
    colpito_destra1=al_load_bitmap("./images/mostro_verde/colpito1_dx.png");
    colpito_destra2=al_load_bitmap("./images/mostro_verde/colpito2_dx.png");

    salta = al_load_bitmap("./images/mostro_verde/salto.png");
    sputa_fuoco_dx = al_load_bitmap("./images/mostro_verde/sputa_fuoco_dx.png");
    sputa_fuoco_sx = al_load_bitmap("./images/mostro_verde/sputa_fuoco_sx.png");
    fuoco1_dx = al_load_bitmap("./images/mostro_verde/fuoco1_dx.png");
    fuoco2_dx = al_load_bitmap("./images/mostro_verde/fuoco2_dx.png");
    fuoco1_sx = al_load_bitmap("./images/mostro_verde/fuoco1_sx.png");
    fuoco2_sx = al_load_bitmap("./images/mostro_verde/fuoco2_sx.png");
}

void Mostro_Verde::drawMostro()
{

    if(vita==false)
    {
        drawSushi();
    }
    else
    {

        if(!colpitoInnevato)
        {
            if(saltando || cadendo)
            {
                al_draw_scaled_bitmap(salta,  0, 0, al_get_bitmap_width(salta), al_get_bitmap_height(salta), x, y, al_get_bitmap_width(salta)+6, al_get_bitmap_height(salta)+6, 0);
            }
            else if(andando_destra && !colpito && !passo && !sparaFuoco)
            {
                al_draw_scaled_bitmap(verso_destra1,  0, 0, al_get_bitmap_width(verso_destra1), al_get_bitmap_height(verso_destra1), x, y, al_get_bitmap_width(verso_destra1)+6, al_get_bitmap_height(verso_destra1)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=true;
                    cont=0;
                }
            }

            else if(andando_destra && !colpito && passo && !sparaFuoco)
            {
                al_draw_scaled_bitmap(verso_destra2,  0, 0, al_get_bitmap_width(verso_destra2),  al_get_bitmap_height(verso_destra2), x, y, al_get_bitmap_width(verso_destra2)+6, al_get_bitmap_height(verso_destra2)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=false;
                    cont=0;
                }
            }
            else if(andando_destra && colpito && !passo)
            {
                al_draw_scaled_bitmap(colpito_destra1,  0, 0, al_get_bitmap_width(colpito_destra1),  al_get_bitmap_height(colpito_destra1), x, y, al_get_bitmap_width(colpito_destra1)+6, al_get_bitmap_height(colpito_destra1)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=true;
                    cont=0;
                }
            }
            else if(andando_destra && colpito && passo)
            {
                al_draw_scaled_bitmap(colpito_destra2,  0, 0, al_get_bitmap_width(colpito_destra2),  al_get_bitmap_height(colpito_destra2), x, y, al_get_bitmap_width(colpito_destra2)+6, al_get_bitmap_height(colpito_destra2)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=false;
                    cont=0;
                }
            }

            else if(andando_sinistra && !colpito && !passo && !sparaFuoco)
            {
                al_draw_scaled_bitmap(verso_sinistra1,  0, 0, al_get_bitmap_width(verso_sinistra1),  al_get_bitmap_height(verso_sinistra1), x, y, al_get_bitmap_width(verso_sinistra1)+6, al_get_bitmap_height(verso_sinistra1)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=true;
                    cont=0;
                }
            }
            else if(andando_sinistra && !colpito && passo && !sparaFuoco)
            {
                al_draw_scaled_bitmap(verso_sinistra2,  0, 0, al_get_bitmap_width(verso_sinistra2),  al_get_bitmap_height(verso_sinistra2), x, y, al_get_bitmap_width(verso_sinistra2)+6, al_get_bitmap_height(verso_sinistra2)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=false;
                    cont=0;
                }
            }
            else if(andando_sinistra && colpito && !passo)
            {
                al_draw_scaled_bitmap(colpito_sinistra1,  0, 0, al_get_bitmap_width(colpito_sinistra1),  al_get_bitmap_height(colpito_sinistra1), x, y, al_get_bitmap_width(colpito_sinistra1)+6, al_get_bitmap_height(colpito_sinistra1)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=true;
                    cont=0;
                }
            }
            else if(andando_sinistra && colpito && passo)
            {
                al_draw_scaled_bitmap(colpito_sinistra2,  0, 0, al_get_bitmap_width(colpito_sinistra2),  al_get_bitmap_height(colpito_sinistra2), x, y, al_get_bitmap_width(colpito_sinistra2)+6, al_get_bitmap_height(colpito_sinistra2)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=false;
                    cont=0;
                }
            }

            if(colpito && nColpito>=1 && nColpito<3)
            {
                al_draw_scaled_bitmap(innevando1, 0, 0, al_get_bitmap_width(innevando1), al_get_bitmap_height(innevando1), x-2, y-9, al_get_bitmap_width(innevando1)+6, al_get_bitmap_height(innevando1)+6, 0);
            }
            else if(colpito && nColpito>=3 && nColpito<5)
            {
                al_draw_scaled_bitmap(innevando2, 0, 0, al_get_bitmap_width(innevando2),   al_get_bitmap_height(innevando2), x-2, y-9, al_get_bitmap_width(innevando2)+6, al_get_bitmap_height(innevando2)+6, 0);

            }
            else if(colpito && nColpito>=5 && nColpito<7)
            {
                al_draw_scaled_bitmap(innevando3, 0, 0, al_get_bitmap_width(innevando3),   al_get_bitmap_height(innevando3), x-2, y-9, al_get_bitmap_width(innevando3)+6, al_get_bitmap_height(innevando3)+6, 0);

            }
            else if(colpito && nColpito>=7)
            {
                al_draw_scaled_bitmap(palladineve1, 0, 0, al_get_bitmap_width(palladineve1),   al_get_bitmap_height(palladineve1), x-2, y-9, al_get_bitmap_width(palladineve1)+6, al_get_bitmap_height(palladineve1)+6, 0);

            }

            if(sparaFuoco && nColpito==0)
            {
                if(fuocoDir)
                {
                    al_draw_scaled_bitmap(sputa_fuoco_dx, 0, 0, al_get_bitmap_width(sputa_fuoco_dx),   al_get_bitmap_height(sputa_fuoco_dx), x, y, al_get_bitmap_width(sputa_fuoco_dx)+6, al_get_bitmap_height(sputa_fuoco_dx)+6, 0);

                    if(passo)
                    {
                        al_draw_scaled_bitmap(fuoco1_dx, 0, 0, al_get_bitmap_width(fuoco1_dx),   al_get_bitmap_height(fuoco1_dx), xFuoco, yFuoco, al_get_bitmap_width(fuoco1_dx)+6, al_get_bitmap_height(fuoco1_dx)+6, 0);
                        cont++;

                        if(cont==7)
                        {
                            passo=false;
                            cont=0;
                        }
                    }
                    else
                    {
                        al_draw_scaled_bitmap(fuoco2_dx, 0, 0, al_get_bitmap_width(fuoco2_dx),   al_get_bitmap_height(fuoco2_dx), xFuoco, yFuoco, al_get_bitmap_width(fuoco2_dx)+6, al_get_bitmap_height(fuoco2_dx)+6, 0);
                        cont++;

                        if(cont==7)
                        {
                            passo=true;
                            cont=0;
                        }
                    }
                }
                else if(!fuocoDir)
                {
                    al_draw_scaled_bitmap(sputa_fuoco_sx, 0, 0, al_get_bitmap_width(sputa_fuoco_sx),   al_get_bitmap_height(sputa_fuoco_sx), x, y, al_get_bitmap_width(sputa_fuoco_sx)+6, al_get_bitmap_height(sputa_fuoco_sx)+6, 0);
                    if(passo)
                    {
                        al_draw_scaled_bitmap(fuoco1_sx, 0, 0, al_get_bitmap_width(fuoco1_sx),   al_get_bitmap_height(fuoco1_sx), xFuoco, yFuoco, al_get_bitmap_width(fuoco1_sx)+6, al_get_bitmap_height(fuoco1_sx)+6, 0);
                        cont++;

                        if(cont==7)
                        {
                            passo=false;
                            cont=0;
                        }
                    }
                    else
                    {
                        al_draw_scaled_bitmap(fuoco2_sx, 0, 0, al_get_bitmap_width(fuoco2_sx),   al_get_bitmap_height(fuoco2_sx), xFuoco, yFuoco, al_get_bitmap_width(fuoco2_sx)+6, al_get_bitmap_height(fuoco2_sx)+6, 0);
                        cont++;

                        if(cont==7)
                        {
                            passo=true;
                            cont=0;
                        }
                    }

                }
            }
        }

        else         //PALLA DI NEVE CHE ROTOLA
        {
            if(!passo)
            {
                al_draw_scaled_bitmap(palladineve1, 0, 0, al_get_bitmap_width(palladineve1),   al_get_bitmap_height(palladineve1), x-2, y-9, al_get_bitmap_width(palladineve1)+6, al_get_bitmap_height(palladineve1)+6, 0);
                cont++;
                if(cont==7)
                {
                    passo=true;
                    cont=0;
                }
            }
            if(passo)
            {
                al_draw_scaled_bitmap(palladineve1, 0, 0, al_get_bitmap_width(palladineve1),   al_get_bitmap_height(palladineve1), x-2, y-9, al_get_bitmap_width(palladineve1)+6, al_get_bitmap_height(palladineve1)+6, 0);
                cont++;
                if(cont==7)
                {
                    passo=false;
                    cont=0;
                }
            }
        }
    }
}

void Mostro_Verde::muovi()
{

    if(colpitoInnevato)
    {
        //al_stop_timer(congelo);
        colpitoEdInnevato();
    }
    else
    {
        if(!cadendo && !saltando)
            diminuisciContPrimaDiSaltare();
        else if(cadendo && saltando)
        {
            contPrimaDiSaltare=1;
            saltando=false;
        }
        if(sparaFuoco)
        {
            if(fuocoDir)
            {
                xFuoco+=2;
                lunghezzaFuoco-=2;
                if(lunghezzaFuoco<=0)
                {
                    sparaFuoco=false;
                    xFuoco=-100;
                    yFuoco=-100;
                    lunghezzaFuoco=50;
                    srand(time(0));
                    contPrimaDiSparare=rand()%100+ 200;

                }

            }
            else if(!fuocoDir)
            {
                xFuoco-=2;
                lunghezzaFuoco-=2;
                if(lunghezzaFuoco<=0)
                {
                    sparaFuoco=false;
                    xFuoco=-100;
                    yFuoco=-100;
                    lunghezzaFuoco=50;
                    srand(time(0));
                    contPrimaDiSparare=rand()%100+ 200;
                }
            }
        }
        else
        {
            if(andando_destra && !colpito && x+15<252) //movimento a dx aggiorna la x che corrisponde alla larghezza schermo
            {
                x+=spostamento;
                contPrimaDiSparare-=spostamento;
                if(contPrimaDiSparare<=0 && !saltando && !cadendo && nColpito==0)
                {
                    fuocoDir=true;
                    sparaFuoco=true;
                    xFuoco=x+15;
                    yFuoco=y;
                    srand((unsigned)time(NULL));
                    contPrimaDiSparare=rand()%300+ 500;
                }
            }
            else if(andando_destra && !colpito && x+15>=252)
            {
                andando_destra=false;
                andando_sinistra=true;
            }

            else if(andando_sinistra && !colpito && x>=0)
            {
                //movimento a sx
                x-=spostamento;
                contPrimaDiSparare-=spostamento;
                if(contPrimaDiSparare<=0 && !saltando && !cadendo && nColpito==0)
                {
                    fuocoDir=false;
                    sparaFuoco=true;
                    xFuoco=x-15;
                    yFuoco=y;
                    srand((unsigned)time(NULL));
                    contPrimaDiSparare=rand()%300+ 500;
                }
            }
            else if(andando_sinistra && !colpito && x<0)
            {
                andando_destra=true;
                andando_sinistra=false;
            }



            if(colpito && al_get_timer_count(congelo)%25==0 )
            {
                nColpito-=1;
                if(nColpito==0)
                {
                    colpito=false;
                    //al_stop_timer(congelo);
                }
                if(nColpito<7)
                {
                    totInnevato=false;
                }
            }

            if(saltando && saltoDistanza<=42 && !cadendo) //aggiorna le posizioni per saltare
            {
                y-=5;
                saltoDistanza+=5;
                if(saltoDistanza>=42)
                {
                    saltando=false;
                    saltoDistanza=0;
                    contPrimaDiSaltare=rand()%200+70;
                    cadendo=true;
                }
            }


        }

    }

}
