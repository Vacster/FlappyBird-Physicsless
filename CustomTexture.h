#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#ifndef CUSTOMTEXTURE_H
#define CUSTOMTEXTURE_H


class CustomTexture
{
    public:
        SDL_Renderer *renderer;
        SDL_Texture *chicken, *deadchicken, *ground, *pipe, *pipe2, *background, *deathmenu, *mainmenu;
        CustomTexture(SDL_Renderer *renderer);
        virtual ~CustomTexture();
    protected:
    private:
};

#endif // CUSTOMTEXTURE_H
