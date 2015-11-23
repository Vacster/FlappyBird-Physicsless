#include "Tubo.h"

Tubo::Tubo(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    x = 1280;

    int w, h;
    tuboup = IMG_LoadTexture(renderer,"tubo.png");
    tubodown = IMG_LoadTexture(renderer, "tubo2.png");
    SDL_QueryTexture(tuboup, NULL, NULL, &w, &h);
    rect.x = x;
    rect.y = 600;
    rect.w = w;
    rect.h = h;

    rect2.x = x;
    rect2.y = 0;
    rect2.w = w;
    rect2.h = h;

    xvel = 10;

}

void Tubo::logica()
{
    rect.x -= xvel;
    rect2.x -= xvel;
    rect.x = rect.x<=-rect.w?x:rect.x;
    rect2.x = rect2.x<=-rect2.w?x:rect2.x;
    SDL_RenderCopy(renderer, tuboup, NULL, &rect);
    SDL_RenderCopy(renderer, tubodown, NULL, &rect2);
}

Tubo::~Tubo()
{
    //dtor
}
