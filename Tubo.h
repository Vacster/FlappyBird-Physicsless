#ifndef TUBO_H
#define TUBO_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define ARRIBA true
#define ABAJO false
#define GAP 100

class Tubo
{
    public:
        SDL_Renderer* renderer;
        SDL_Texture *tuboup, *tubodown;
        SDL_Rect rect, rect2;
        float x, y, xvel;
        bool direction;
        Tubo(SDL_Renderer* renderer);
        virtual ~Tubo();
        void logica();
    protected:
    private:
};

#endif // TUBO_H
