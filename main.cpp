#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <stdio.h>

#include "Bird.h"
#include "Tubo.h"
#include "ground.h"
#include "Background.h"
#include "ObjetoMovible.h"
#include "CustomTexture.h"
#include "RegularTexture.h"

#define TICK_INTERVAL 17
#define FALLING_CONSTANT -11.5

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Rect message_rect, flash, *startrect, *mainexitrect, *restartrect, *deathexitrect;
SDL_Texture *message;
SDL_Surface *surfaceMessage;
SDL_Event Event;
SDL_Color textcolor, colors[4];

int *counter, *mouse_x, *mouse_y;
float pollitomurioen;
bool down = false;
enum Screen {MAIN, PAUSE, DEATH, RUN};
static Uint32 next_time, now;
const Uint8 *state;

TTF_Font *font;

Bird *pollito;
Background *background;
RegularTexture *texture;
Screen screen;

std::list<ObjetoMovible*>objetos;

void initrects();
void restart();
void changeskin(int i);
bool collision(SDL_Rect a, SDL_Point b, int radius);
bool clickin(SDL_Rect* rect);
Uint32 time_left(void);

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int main( int argc, char* args[] )
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return 10;

    if((window = SDL_CreateWindow("Flappy Pollito v0.2", 100, 100,
    1360, 720, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
        return 20;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_GL_SetSwapInterval(1);

    if (renderer == NULL)
        return 30;

    state = SDL_GetKeyboardState(NULL);
    next_time = SDL_GetTicks() + TICK_INTERVAL;

    screen = MAIN;

    mouse_x = new int(0);
    mouse_y = new int(0);
    counter = new int(0);

    texture = new RegularTexture(renderer, 0);

    objetos.push_back(new Background(renderer, texture));
    objetos.push_back(new Tubo(renderer, texture, counter));
    objetos.push_back(new ground(renderer, texture));
    pollito = new Bird(renderer, texture);

    TTF_Init();
    font = TTF_OpenFont("text.ttf", 200);
    colors[0] = {255, 255, 255};
    colors[1] = {169, 231, 227};
    colors[2] = {0, 0, 0};
    colors[3] = {255, 255, 255};
    textcolor = colors[0];

    initrects();

    state = SDL_GetKeyboardState(NULL);


    while(true)
    {
        switch(screen){
            case RUN:
                while(SDL_PollEvent(&Event))
                {
                    if(Event.type == SDL_QUIT)
                        return 0;
                    if(state[SDL_SCANCODE_SPACE] && !down)
                    {
                        down = true;
                        pollito->yvel = FALLING_CONSTANT;
                    }
                    if(!state[SDL_SCANCODE_SPACE] && down)
                        down = false;
                }

                surfaceMessage = TTF_RenderText_Solid(font, patch::to_string(*counter).c_str(), textcolor);
                message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

                for(std::list<ObjetoMovible*>::iterator e = objetos.begin(); e!=objetos.end(); e++)
                {
                    if((collision((*e)->rect, pollito->point, pollito->radius)
                    || collision((*e)->rect2, pollito->point, pollito->radius))
                    && (*e)->tipo!="Background")
                    {
                        now = SDL_GetTicks();
                        while(SDL_GetTicks() < now+50)
                        {
                            SDL_RenderCopy(renderer, texture->flash, NULL, &flash);
                            SDL_RenderPresent(renderer);
                        }
                        pollitomurioen = (float) pollito->rect.y;
                        pollito->muerte(pollitomurioen);
                        screen = DEATH;
                    }
                    (*e)->logica();
                }

                SDL_RenderCopy(renderer, message, NULL, &message_rect);
                pollito->logica();
            break;

            case MAIN:
                SDL_RenderCopy(renderer, texture->mainmenu, NULL, &flash);
                while(SDL_PollEvent(&Event))
                {
                    if(Event.type == SDL_QUIT)
                        return 0;
                    if(Event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if(clickin(startrect))
                            screen = RUN;
                        else if(clickin(mainexitrect))
                            return 0;
                    }
                    if(state[SDL_SCANCODE_1])
                        changeskin(0);
                    else if(state[SDL_SCANCODE_2])
                        changeskin(1);
                    else if(state[SDL_SCANCODE_3])
                        changeskin(2);
                    else if(state[SDL_SCANCODE_4])
                        changeskin(3);
                }
            break;

            case DEATH:
                while(SDL_PollEvent(&Event))
                {
                    switch(Event.type){
                        case SDL_QUIT:
                            return 0;
                        break;

                        case SDL_MOUSEBUTTONDOWN:
                            if(pollito->rect_menu.y <= 110){
                                if(clickin(restartrect))
                                    restart();
                                else if(clickin(deathexitrect))
                                {
                                    restart();
                                    screen = MAIN;
                                }
                            }
                        break;
                    }
                }
                for(std::list<ObjetoMovible*>::iterator e = objetos.begin(); e!=objetos.end(); e++)
                {
                    SDL_RenderCopy(renderer, (*e)->texture2, NULL, &(*e)->rect);
                    SDL_RenderCopy(renderer, (*e)->texture, NULL, &(*e)->rect2);
                }
                SDL_RenderCopy(renderer, message, NULL, &message_rect);
                pollito->muerte(pollitomurioen);

            break;

            default:
            break;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }

	return 0;
}

void changeskin(int i)
{
    delete pollito;
    delete texture;

    textcolor = colors[i];
    texture = new RegularTexture(renderer, i);
    objetos.clear();
    objetos.push_back(new Background(renderer, texture));
    objetos.push_back(new Tubo(renderer, texture, counter));
    objetos.push_back(new ground(renderer, texture));
    pollito = new Bird(renderer, texture);
}

void restart()
{
    objetos.clear();
    objetos.push_back(new Background(renderer, texture));
    objetos.push_back(new Tubo(renderer, texture, counter));
    objetos.push_back(new ground(renderer, texture));
    pollito = new Bird(renderer, texture);
    *counter = 0;
    pollitomurioen = 0;
    screen = RUN;
}

void initrects()
{
    startrect = new SDL_Rect();
    mainexitrect = new SDL_Rect();
    restartrect = new SDL_Rect();
    deathexitrect = new SDL_Rect();

    message_rect = {590, 5, 100, 100};
    flash = {0, 0, 1360, 720};
    *startrect = {488, 305, 352, 145};
    *mainexitrect = {488, 500, 352, 145};
    *restartrect = {520, 290, 300, 100};
    *deathexitrect = {520, 440, 300, 100};
}

bool clickin(SDL_Rect* rect)
{
    SDL_GetMouseState(mouse_x, mouse_y);
    if(*mouse_x <= (rect->x+rect->w) && *mouse_x >= rect->x
    && *mouse_y <= (rect->y+rect->h) && *mouse_y >= rect->y)
            return true;
    return false;
}

bool collision(SDL_Rect rect, SDL_Point circle, int radius)
{
    int circleDistancex, circleDistancey;
    float cornerDistance_sq;

    circleDistancex = abs(circle.x - (rect.x+(rect.w/2)));
    circleDistancey = abs(circle.y - (rect.y+(rect.h/2)));

    if (circleDistancex > (rect.w/2 + radius))
        return false;
    if (circleDistancey > (rect.h/2 + radius))
        return false;

    if (circleDistancex <= ((rect.w/2)+radius))
        return true;
    if (circleDistancey <= ((rect.h/2)+radius))
        return true;

    cornerDistance_sq = ((circleDistancex - rect.w/2)^2) +
                        ((circleDistancey - rect.h/2)^2);

    return (cornerDistance_sq <= (radius^2));
}


Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}
