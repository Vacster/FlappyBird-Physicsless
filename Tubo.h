#ifndef TUBO_H
#define TUBO_H
#include "ObjetoMovible.h"
#include <time.h>
#define ABAJO true
#define ARRIBA false

class Tubo : public ObjetoMovible
{
    public:
        SDL_Renderer* renderer;
        int gap, *counter;
        bool paso;
        Tubo(SDL_Renderer* renderer, int* counter);
        virtual ~Tubo();
        void logica();
    protected:
    private:
};

#endif // TUBO_H
