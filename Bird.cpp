#include "Bird.h"

Bird::Bird(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->x = 220.0f;
    this->y = 250.0f;
    yvel = 3.0f;
    yacc = 0.5f;

    int w,h;
    character = IMG_LoadTexture(renderer,"pollo.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Bird::logica()
{
    yvel -= yvel>3.0f?0.1f:0;
    yvel += yacc;
    rect.y += yvel;

    SDL_RenderCopy(renderer, character, NULL, &rect);
}

void Bird::muerte()
{
    //TODO
}

Bird::~Bird()
{
    //dtor
}
