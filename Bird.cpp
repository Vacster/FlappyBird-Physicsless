#include "Bird.h"


Bird::Bird(SDL_Renderer* renderer, RegularTexture *texture)
{
    this->renderer = renderer;

    yvel = 3.0f;
    yacc = 0.5f;
    radius = 31;

    subio = false;

    int w,h;
    character = texture->chicken;
    charactermuerto = texture->deadchicken;
    death_menu = texture->deathmenu;
    SDL_QueryTexture(character, NULL, NULL, &w, &h);

    rect = {220, 250, w, h};
    rect_menu = {360, 720, 600, 500};

    point.x = rect.x + radius;
    point.y = rect.y + radius;
}

void Bird::logica()
{
    yvel -= yvel>3.0f?0.1f:0;
    yvel += yacc;
    rect.y += yvel;
    point.y = rect.y + radius;

    if(rect.y >= 720 - rect.h)
        rect.y = 720-rect.h;
    SDL_RenderCopy(renderer, character, NULL, &rect);
}

void Bird::muerte(float startpos)
{
    if(subio)
    {
        yvel -= yvel>3.0f?0.2f:0;
        yvel += yacc;
    }
    else
    {
        if(rect.y <= startpos-50)
            subio = true;
        else
            yvel = -10.0f;
    }

    if(rect.y <= 1360)
        SDL_RenderCopy(renderer, charactermuerto, NULL, &rect);
    else
    {
        if(rect_menu.y >= 110.0f)
            rect_menu.y -= 30.0f;
        SDL_RenderCopy(renderer, death_menu, NULL, &rect_menu);
    }
    rect.y += yvel;
}

Bird::~Bird(){}
