#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "ObjetoMovible.h"


class Background : public ObjetoMovible
{
    public:
        void logica();
        Background(SDL_Renderer* renderer, RegularTexture *texture);
        virtual ~Background();
    protected:
    private:
};

#endif // BACKGROUND_H
