#ifndef GROUND_H
#define GROUND_H
#include "ObjetoMovible.h"

class ground : public ObjetoMovible
{
    public:
        void logica();
        virtual ~ground();
        ground(SDL_Renderer* renderer, RegularTexture *texture);
};

#endif // GROUND_H
