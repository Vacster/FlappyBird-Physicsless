#include "Tubo.h"

int min = 100, max = 450;

Tubo::Tubo(SDL_Renderer* renderer, int* counter)
{
    this->renderer = renderer;
    x = 1360;
    gap = 720;
    this->counter = counter;

    int w, h;
    texture = IMG_LoadTexture(renderer,"tubo.png");
    texture2 = IMG_LoadTexture(renderer, "tubo2.png");
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    rect.x = -100; //lmao
    rect.w = w;
    rect.h = h;
    rect2.w = w;
    rect2.h = h;

    paso = true;
}

void Tubo::logica()
{
    rect.x -= xvel;
    rect2.x -= xvel;

    if(rect.x <= -rect.w)
    {
        srand(time(NULL));
        paso = false;
        rect.x = x;
        rect2.x = x;
        rect.y = -(min + (rand() % (int)(max - min + 1)));
        rect2.y = rect.y + gap;
    }

    if(!paso && rect.x <= 220)
    {
        paso = true;
        *counter+=1;
    }

    SDL_RenderCopy(renderer, texture2, NULL, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
}

Tubo::~Tubo(){}
