#include "Tubo.h"

int min = 100, max = 450;

Tubo::Tubo(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    xvel = 10;
    x = 1280;
    gap = 720;
    puntos = 0;

    int w, h;
    tuboup = IMG_LoadTexture(renderer,"tubo.png");
    tubodown = IMG_LoadTexture(renderer, "tubo2.png");
    SDL_QueryTexture(tuboup, NULL, NULL, &w, &h);

    rect.w = w;
    rect.h = h;
    rect2.w = w;
    rect2.h = h;

    paso = false;
    endPos();
}

void Tubo::logica()
{
    rect.x -= xvel;
    rect2.x -= xvel;

    if(rect.x <= -rect.w){endPos();}
    if(!paso && rect.x <= 220){pasa();}

    SDL_RenderCopy(renderer, tubodown, NULL, &rect);
    SDL_RenderCopy(renderer, tuboup, NULL, &rect2);
}

void Tubo::pasa()
{
    paso = true;
    puntos++;
    std::cout<<puntos<<std::endl;

}

void Tubo::endPos(){
    srand(time(NULL));
    paso = false;
    rect.x = x;
    rect2.x = x;
    rect.y = -(min + (rand() % (int)(max - min + 1)));
    rect2.y = rect.y + gap;
}

Tubo::~Tubo(){}
