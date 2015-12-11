#ifndef FLOWER_H
#define FLOWER_H

#include "ObjetoMovible.h"

class Flower : public ObjetoMovible
{
    public:
        SDL_Texture *textures[4];

        int frames, texture_num;

        void logica();
        virtual ~Flower();
        Flower(SDL_Renderer* renderer);
    protected:
    private:
};

#endif // FLOWER_H
