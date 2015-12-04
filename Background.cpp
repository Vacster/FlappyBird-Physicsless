#include "Background.h"

Background::Background(SDL_Renderer* renderer)
{
    this->renderer = renderer;

    int w, h;
    texture = IMG_LoadTexture(renderer,"fondo.png");
    texture2 = texture;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;

    rect2.x = 1280;
    rect2.y = rect.y;
    rect2.w = rect.w;
    rect2.h = rect.h;
}

void Background::logica()
{
    rect.x -= xvel;
    rect2.x -= xvel;

    if(rect.x <= -rect.w)
    {
        rect.x = 1280;
    }
    if(rect2.x <= -rect2.w)
    {
        rect2.x = 1280;
    }

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
}

Background::~Background()
{
    //dtor
}
