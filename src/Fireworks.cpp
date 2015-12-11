#include "Fireworks.h"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int curr;

Fireworks::Fireworks(SDL_Renderer *renderer, int *puntos)
{
    this->renderer = renderer;
    this->puntos = puntos;
    curr = 0;

    rect = {850, 50, 300, 300}; //TODO ARREGLAR TODO

    texture[0] = &zero;
    texture[1] = &one;
    texture[2] = &two;
    texture[3] = &three;
    texture[4] = &four;
    texture[5] = &five;
    texture[6] = &six;
    texture[7] = &seven;
    texture[8] = &eight;

    for(int x = 0; x < 9; x++)
    {
        *texture[x] = IMG_LoadTexture(renderer, ("images/fireworks/"+patch::to_string(x)+".png").c_str());
    }
    frames = 0;
}

void Fireworks::logica()
{
    if(*puntos > 3 && *puntos < 5)
        SDL_RenderCopy(renderer, *texture[curr], NULL, &rect);

    frames++;
    if(frames%8==0)
    {
        curr+=curr>8?-9:1;
    }
}

Fireworks::~Fireworks()
{
    //dtor
}
