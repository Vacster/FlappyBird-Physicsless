#include "../include/RegularTexture.h"

RegularTexture::RegularTexture(SDL_Renderer *renderer, int skin)
{
    this->renderer = renderer;
    textures[0] = &chicken;
    textures[1] = &deadchicken;
    textures[2] = &ground;
    textures[3] = &pipe;
    textures[4] = &pipe2;
    textures[5] = &background;
    textures[6] = &deathmenu;
    textures[7] = &mainmenu;
    textures[8] = &flash;

    items[0] = "pollo.png";
    items[1] = "pollomuerto.png";
    items[2] = "ground.png";
    items[3] = "tubo.png";
    items[4] = "tubo2.png";
    items[5] = "fondo.png";
    items[6] = "deathmenu.png";
    items[7] = "mainmenu.png";
    items[8] = "flash.png";

    switch(skin)
    {
        case BLUE:
            location = "assets/blue/";
        break;
        case SPACE:
            location = "assets/space/";
        break;
        case REGULAR:
            location = "assets/regular/";
        break;
        case BLACKNWHITE:
            location = "assets/blacknwhite/";
        break;
    }
    for(int x = 0; x<9; x++)
        *textures[x] = IMG_LoadTexture(renderer, (location+items[x]).c_str());
}

RegularTexture::~RegularTexture()
{
    //dtor
}
