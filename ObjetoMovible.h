#ifndef OBJETOMOVIBLE_H
#define OBJETOMOVIBLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "RegularTexture.h"

#define xvel 10

class ObjetoMovible
{
    public:
        SDL_Rect rect, rect2;
        SDL_Renderer* renderer;
        SDL_Texture *texture, *texture2;

        std::string tipo;

        ObjetoMovible() {}
        virtual void logica()=0;
        virtual ~ObjetoMovible() {}
};

#endif // OBJETOMOVIBLE_H
