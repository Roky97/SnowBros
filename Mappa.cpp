#include "Mappa.h"
Mappa::Mappa()
{
    loadcounterX=loadcounterY=0;
}
Mappa::~Mappa()
{
    // if(!tile==NULL)
    // al_destroy_bitmap(tile);
}

int Mappa::getMapSizeX()
{
    return mapsizeX;
}
int Mappa::getMapSizeY()
{
    return mapsizeY;
}

void Mappa::caricaMappa(const char* nomefile)
{
    ifstream openfile(nomefile);
    if(openfile.is_open())
    {
        openfile>>mapsizeX>>mapsizeY;

        while(!openfile.eof())
        {
            openfile >> map[loadcounterX][loadcounterY];
            loadcounterX++;

            if(loadcounterX >=mapsizeX)
            {
                loadcounterX=0;
                loadcounterY++;
            }
        }
        mapsizeY=loadcounterY++;
    }
}

void Mappa::drawMappa() //devo creare gli elentibitmap(mattoni, mostri o altre cose) per ogni tipo di mappa
{
    //cout<<mapsizeX<<" "<<mapsizeY<<endl;
    for(int i=0; i<mapsizeX; i++)
    {
        for(int j=0; j<mapsizeY; j++)
        {
            if(map[i][j] == 1)
            {
                al_draw_bitmap(tile, i*21, j*21, 0);
            }
        }
    }
}

void Mappa::caricaElementi(const char* image)
{
    tile= al_load_bitmap(image);
}

int Mappa::getValore(int a, int b)
{
    return map[a][b];
}
