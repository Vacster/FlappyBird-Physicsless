#include "ground.h"

ground::ground(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    xvel = 10;
    x = 1280;

    int w, h;
    piso = IMG_LoadTexture(renderer,"ground.png");
    SDL_QueryTexture(piso, NULL, NULL, &w, &h);

    rect.x = 0;
    rect.y = 720-30;
    rect2.x = x;
    rect2.y = rect.y;
    rect.w = w;
    rect.h = 30;
    rect2.w = w;
    rect2.h = 30;
}

void ground::logica()
{
    rect.x -= xvel;
    rect2.x -= xvel;

    if(rect.x <= -rect.w)
    {
        rect.x = 1280;
    }
    if(rect2.x <= -rect.w)
    {
        rect2.x = 1280;
    }



    SDL_RenderCopy(renderer, piso, NULL, &rect);
    SDL_RenderCopy(renderer, piso, NULL, &rect2);
}

ground::~ground()
{
    //dtor
}
