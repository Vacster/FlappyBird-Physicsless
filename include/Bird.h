#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RegularTexture.h"

#ifndef BIRD_H
#define BIRD_H


class Bird
{
    public:

        SDL_Point point;
        SDL_Renderer* renderer;
        SDL_Rect rect, rect_menu;
        SDL_Texture *character, *charactermuerto, *death_menu;

        int radius;
        bool subio;
        float yvel, yacc;

        void logica();
        virtual ~Bird();
        void muerte(float startpos);
        Bird(SDL_Renderer* renderer, RegularTexture *texture);

    protected:
    private:
};

#endif // BIRD_H
