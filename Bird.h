#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RegularTexture.h"
#ifndef BIRD_H
#define BIRD_H


class Bird
{
    public:
        SDL_Renderer* renderer;
        SDL_Texture *character, *charactermuerto, *death_menu;
        SDL_Rect rect, rect_menu;
        SDL_Point point;
        bool subio;
        int radius;
        float yvel, yacc;
        Bird(SDL_Renderer* renderer, RegularTexture *texture);
        virtual ~Bird();
        void logica();
        void muerte(float startpos);
    protected:
    private:
};

#endif // BIRD_H
