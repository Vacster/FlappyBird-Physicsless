#include "ground.h"

ground::ground(SDL_Renderer *renderer, RegularTexture *texture)
{
    this->renderer = renderer;
    tipo = "Ground";

    this->texture = texture->ground;
    texture2 = this->texture;

    rect = {0, 690, 1360, 30};
    rect2 = {1360, 690, 1360, 30};
}

void ground::logica()
{
    rect.x -= xvel;
    rect2.x -= xvel;

    if(rect.x <= -rect.w)
        rect.x = 1360;
    if(rect2.x <= -rect2.w)
        rect2.x = 1360;

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
}

ground::~ground(){}
