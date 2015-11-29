#ifndef GROUND_H
#define GROUND_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class ground
{
    public:
        SDL_Renderer* renderer;
        SDL_Texture *piso;
        SDL_Rect rect, rect2;
        float x, y, xvel;
        void logica();
        ground(SDL_Renderer* renderer);
        virtual ~ground();
    protected:
    private:
};

#endif // GROUND_H
