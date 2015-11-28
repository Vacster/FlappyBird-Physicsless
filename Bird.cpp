#include "Bird.h"

Bird::Bird(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->x = 220.0f;
    this->y = 250.0f;
    yvel = 3.0f;
    yacc = 0.5f;
    radius = 31;

    int w,h;
    character = IMG_LoadTexture(renderer,"pollo.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    point.x = rect.x + radius;
    point.y = rect.y + radius;
}

void Bird::logica()
{
    yvel -= yvel>3.0f?0.1f:0;
    yvel += yacc;
    rect.y += yvel;
    point.y = rect.y + radius;
    if(rect.y >= 720 - rect.h){rect.y = 720-rect.h;}
    SDL_RenderCopy(renderer, character, NULL, &rect);
}

void Bird::muerte()
{
    character = IMG_LoadTexture(renderer, "pollomuerto.png");
    yvel = 3.0f;
}

Bird::~Bird(){}
