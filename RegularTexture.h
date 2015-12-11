#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <list>
#include <string>

#ifndef REGULARTEXTURE_H
#define REGULARTEXTURE_H

#define BLUE 1
#define SPACE 3
#define REGULAR 0
#define BLACKNWHITE 2

class RegularTexture
{
    public:
        SDL_Renderer *renderer;
        SDL_Texture **textures[9];

        std::string items[9];
        std::string location;

        virtual ~RegularTexture();
        RegularTexture(SDL_Renderer *renderer, int skin);
        SDL_Texture *chicken, *deadchicken, *ground, *pipe, *pipe2, *background, *deathmenu, *mainmenu, *flash;
};

#endif // REGULARTEXTURE_H
