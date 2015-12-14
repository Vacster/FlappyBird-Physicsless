#include "../include/Background.h"

Background::Background(SDL_Renderer *renderer, RegularTexture *texture)
{
    this->renderer = renderer;
    tipo = "Background";

    this->texture = texture->background;
    texture2 = this->texture;

    rect = {0, 0, 1360, 720};
    rect2 = {1360, 0, 1360, 720};
}

void Background::logica()
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

Background::~Background()
{
    //dtor
}
