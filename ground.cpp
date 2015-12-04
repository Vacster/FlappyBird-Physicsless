#include "ground.h"

ground::ground(SDL_Renderer* renderer)
{
    this->renderer = renderer;

    int w, h;
    texture = IMG_LoadTexture(renderer,"ground.png");
    texture2 = texture;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    rect.x = 0;
    rect.y = 690;
    rect.w = w;
    rect.h = 30;

    rect2.x = 1360;
    rect2.y = rect.y;
    rect2.w = rect.w;
    rect2.h = rect.h;
}

void ground::logica()
{
    rect.x -= xvel;
    rect2.x -= xvel;

    if(rect.x <= -rect.w)
    {
        rect.x = 1360;
    }
    if(rect2.x <= -rect2.w)
    {
        rect2.x = 1360;
    }

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
}

ground::~ground()
{
    //dtor
}
