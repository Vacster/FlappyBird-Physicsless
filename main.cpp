#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<list>
#include <sstream>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Bird.h"
#include "Tubo.h"
#include "ground.h"
#include "ObjetoMovible.h"
#include "Background.h"

#define TICK_INTERVAL 17
#define FALLING_CONSTANT -11.5

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
int *counter;
bool down = false;
static Uint32 next_time;

TTF_Font *font;
SDL_Color textcolor;
SDL_Surface* surfaceMessage;
SDL_Texture* message;
SDL_Rect message_rect;

bool collision(SDL_Rect a, SDL_Point b, int radius);
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

    enum Screen {MAIN, PAUSE, DEATH, RUN};

    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Survival Game", 100, 100, 1280/*WIDTH*/, 720/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_GL_SetSwapInterval(1);

    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Que corra a la misma velocidad en diferentes computadoras
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    next_time = SDL_GetTicks() + TICK_INTERVAL;

    counter = new int(0);

    std::list<ObjetoMovible*>objetos;

    objetos.push_back(new Tubo(renderer, counter));
    objetos.push_back(new ground(renderer));
    Background* background = new Background(renderer);
    Bird* pollito = new Bird(renderer);


    TTF_Init();
    font = TTF_OpenFont("text.ttf", 200);
    textcolor = {255,255,255};
    surfaceMessage = TTF_RenderText_Solid(font, patch::to_string(counter).c_str(), textcolor);
    message = SDL_CreateTextureFromSurface( renderer, surfaceMessage );
    message_rect.x = 590;
    message_rect.y = 5;
    message_rect.w = 100;
    message_rect.h = 100;

    SDL_Rect flash;
    flash.h = 720;
    flash.w = 1280;
    flash.x = 0;
    flash.y = 0;

    SDL_Texture *flash_Texture = IMG_LoadTexture(renderer,"flash.png");

    float pollitomurioen;

    state = SDL_GetKeyboardState(NULL);

    Screen screen = RUN;//TODO: cambiar a MAIN

    //Main Loop
    while(true)
    {
        switch(screen){
            case RUN:

                while(SDL_PollEvent(&Event))
                {
                    switch(Event.type){
                        case SDL_QUIT:
                            return 0;
                            break;
                    }
                    if(state[SDL_SCANCODE_SPACE] && !down)
                    {
                        down = true;
                        pollito->yvel = FALLING_CONSTANT;
                    }
                    if(!state[SDL_SCANCODE_SPACE] && down)
                    {
                        down = false;
                    }

                }

                surfaceMessage = TTF_RenderText_Solid(font, patch::to_string(*counter).c_str(), textcolor);
                message = SDL_CreateTextureFromSurface( renderer, surfaceMessage );

                background->logica();
                for(std::list<ObjetoMovible*>::iterator e = objetos.begin(); e!=objetos.end(); e++)
                {
                    if(collision((*e)->rect, pollito->point, pollito->radius) || collision((*e)->rect2, pollito->point, pollito->radius))
                    {
                        Uint32 now = SDL_GetTicks();
                        while(SDL_GetTicks() < now+60)
                        {
                            SDL_RenderCopy(renderer, flash_Texture, NULL, &flash);
                            SDL_RenderPresent(renderer);
                        }
                        screen = DEATH;
                        pollitomurioen = (float)pollito->rect.y;
                        pollito->muerte(pollitomurioen);
                    }
                    (*e)->logica();
                }

                SDL_RenderCopy(renderer, message, NULL, &message_rect);
                pollito->logica();

                break;

            case MAIN:
                //TODO: MAIN
                break;

            case PAUSE:
                //TODO: PAUSE
                break;

            case DEATH:
                SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);
                SDL_RenderCopy(renderer, background->texture2, NULL, &background->rect2);
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

bool collision(SDL_Rect rect, SDL_Point circle, int radius)
{
    int circleDistancex, circleDistancey;
    float cornerDistance_sq;

    circleDistancex = abs(circle.x - (rect.x+(rect.w/2)));
    circleDistancey = abs(circle.y - (rect.y+(rect.h/2)));

    if (circleDistancex > (rect.w/2 + radius)) { return false; }
    if (circleDistancey > (rect.h/2 + radius)) { return false; }

    if (circleDistancex <= ((rect.w/2)+radius)) { return true; }
    if (circleDistancey <= ((rect.h/2)+radius)) { return true; }

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

