#ifndef GROUND_H
#define GROUND_H
#include "ObjetoMovible.h"


class ground : public ObjetoMovible
{
    public:
        void logica();
        ground(SDL_Renderer* renderer);
        virtual ~ground();
    protected:
    private:
};

#endif // GROUND_H
