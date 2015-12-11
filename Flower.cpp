#include "Flower.h"


Flower::Flower(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    tipo = "Flower";

    frames = 0, texture_num = 0;

    textures[0] = IMG_LoadTexture(renderer, "flower_straight.png");
    textures[1] = IMG_LoadTexture(renderer, "flower_left.png");
    textures[2] = IMG_LoadTexture(renderer, "flower_straight.png");
    textures[3] = IMG_LoadTexture(renderer, "flower_right.png");

    texture = textures[texture_num];
    texture2 = textures[texture_num];

    rect = {500, 630, 76, 67};
    rect2 = {1200, 630, 76, 67};
}

void Flower::logica()
{
    frames++;
    if(frames%14==0)
    {
        texture_num+=texture_num>2?-3:1;
        texture = textures[texture_num];
        texture2 = textures[texture_num];
    }

    rect.x -= xvel;
    rect2.x -= xvel;

    if(rect.x <= -rect.w)
        rect.x = 1360;
    if(rect2.x <= -rect2.w)
        rect2.x = 1360;

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
}

Flower::~Flower(){}
