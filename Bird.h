#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef BIRD_H
#define BIRD_H


class Bird
{
    public:
        SDL_Renderer* renderer;
        SDL_Texture *character, *charactermuerto;
        SDL_Rect rect;
        SDL_Point point;
        bool subio;
        int radius;
        float x, y, yvel, yacc;
        Bird(SDL_Renderer* renderer);
        virtual ~Bird();
        void logica();
        void muerte(float startpos);
    protected:
    private:
};

#endif // BIRD_H
