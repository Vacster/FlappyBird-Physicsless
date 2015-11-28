#ifndef TUBO_H
#define TUBO_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <iostream>
#define ABAJO true
#define ARRIBA false

class Tubo
{
    public:
        SDL_Renderer* renderer;
        SDL_Texture *tuboup, *tubodown;
        SDL_Rect rect, rect2;
        float x, y, xvel;
        int gap, puntos;
        bool direction, paso;
        Tubo(SDL_Renderer* renderer);
        virtual ~Tubo();
        void logica();
        void pasa();
        void endPos();
    protected:
    private:
};

#endif // TUBO_H
