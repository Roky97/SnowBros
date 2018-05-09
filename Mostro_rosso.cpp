#include "Mostro_rosso.h"

Mostro_rosso::Mostro_rosso()
{
    Mostro();
    saltando =false;
    // andando_destra=true;
    // andando_sinistra=false;
    colpito=false;
    nColpito=0;
    al_start_timer(congelo);
    tipo=0;

}

Mostro_rosso::Mostro_rosso(float x1, float y2)
{
    Mostro(x1,y2);
    saltando=false;
    andando_destra=true;
    andando_sinistra=false;
    colpito=false;
    nColpito=0;
    tipo=0;
}
Mostro_rosso::~Mostro_rosso()
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



void Mostro_rosso::carica_immagini()
{
    verso_sinistra1=al_load_bitmap("./images/mostro_rosso/sinistra_1.png");
    verso_sinistra2=al_load_bitmap("./images/mostro_rosso/sinistra_2.png");
    colpito_sinistra1=al_load_bitmap("./images/mostro_rosso/colpito_sx1.png");
    colpito_sinistra2=al_load_bitmap("./images/mostro_rosso/colpito_sx2.png");

    verso_destra1=al_load_bitmap("./images/mostro_rosso/destra_1.png");
    verso_destra2=al_load_bitmap("./images/mostro_rosso/destra_2.png");
    colpito_destra1=al_load_bitmap("./images/mostro_rosso/colpito_dx1.png");
    colpito_destra2=al_load_bitmap("./images/mostro_rosso/colpito_dx2.png");

    salta = al_load_bitmap("./images/mostro_rosso/salto.png");
}

void Mostro_rosso::drawMostro()
{

    if(!vita)
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
            else if(andando_destra && !colpito && !passo)
            {
                al_draw_scaled_bitmap(verso_destra1,  0, 0, al_get_bitmap_width(verso_destra1), al_get_bitmap_height(verso_destra1), x, y, al_get_bitmap_width(verso_destra1)+6, al_get_bitmap_height(verso_destra1)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=true;
                    cont=0;
                }
            }

            else if(andando_destra && !colpito && passo)
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

            else if(andando_sinistra && !colpito && !passo)
            {
                al_draw_scaled_bitmap(verso_sinistra1,  0, 0, al_get_bitmap_width(verso_sinistra1),  al_get_bitmap_height(verso_sinistra1), x, y, al_get_bitmap_width(verso_sinistra1)+6, al_get_bitmap_height(verso_sinistra1)+6, 0);
                cont++;

                if(cont==7)
                {
                    passo=true;
                    cont=0;
                }
            }
            else if(andando_sinistra && !colpito && passo)
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
                al_draw_scaled_bitmap(palladineve2, 0, 0, al_get_bitmap_width(palladineve2),   al_get_bitmap_height(palladineve2), x-2, y-9, al_get_bitmap_width(palladineve2)+6, al_get_bitmap_height(palladineve2)+6, 0);
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

void Mostro_rosso::muovi()
{

    if(colpitoInnevato)
    {
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
        if(andando_destra && !colpito && x+20<252) //movimento a dx aggiorna la x che corrisponde alla larghezza schermo
        {
            x+=spostamento;
        }
        else if(andando_destra && !colpito && x+20>=252)
        {
            andando_destra=false;
            andando_sinistra=true;
        }

        else if(andando_sinistra && !colpito && x>=0) //movimento a sx
            x-=spostamento;
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
                contPrimaDiSaltare=rand()%200+50;
                cadendo=true;
            }
        }
    }

}
