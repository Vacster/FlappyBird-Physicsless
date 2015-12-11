#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <sstream>
#ifndef FIREWORKS_H
#define FIREWORKS_H


class Fireworks
{
    public:
        int *puntos, frames;
        Fireworks(SDL_Renderer *renderer, int *puntos);
        SDL_Rect rect;
        SDL_Texture **texture[9];
        SDL_Texture *zero, *one, *two, *three, *four, *five, *six, *seven, *eight;
        SDL_Renderer *renderer;
        void logica();
        virtual ~Fireworks();
    protected:
    private:
};

#endif // FIREWORKS_H
