#include "Tubo.h"

int min = 100, max = 450;

Tubo::Tubo(SDL_Renderer *renderer, RegularTexture *texture,int *counter)
{
    this->renderer = renderer;
    this->counter = counter;
    tipo = "Tubo";

    int w, h;
    this->texture = texture->pipe;
    this->texture2 = texture->pipe2;
    SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);

    gap = 690;
    rect = {-100, 0, w, h};
    rect2 = {-100, 0, w, h};

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
        rect.x = 1360;
        rect2.x = 1360;
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
