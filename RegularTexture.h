#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
#include <string>

#ifndef REGULARTEXTURE_H
#define REGULARTEXTURE_H
#define REGULAR 0
#define BLUE 1
#define BLACKNWHITE 2
#define SPACE 3

class RegularTexture
{
    public:
        SDL_Renderer *renderer;
        std::string items[9];
        std::string location;
        SDL_Texture **textures[9];
        SDL_Texture *chicken, *deadchicken, *ground, *pipe, *pipe2, *background, *deathmenu, *mainmenu, *flash;
        RegularTexture(SDL_Renderer *renderer, int skin);
        virtual ~RegularTexture();
    protected:
    private:
};

#endif // REGULARTEXTURE_H
