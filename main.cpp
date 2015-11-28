#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<SDL/SDL_mixer.h>
#include "Bird.h"
#include "Tubo.h"
#define TICK_INTERVAL 17
#define FALLING_CONSTANT -11.5
#define PRESSED true
#define NOT_PRESSED false

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background;
SDL_Rect rect_background;
static Uint32 next_time;

bool collision(SDL_Rect a, SDL_Point b, int radius);
void restart(SDL_Rect *a, SDL_Rect *b, SDL_Rect *c);

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
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

    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    //Que corra a la misma velocidad en diferentes computadoras
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    next_time = SDL_GetTicks() + TICK_INTERVAL;

    Bird* pollito = new Bird(renderer);
    Tubo* tubito = new Tubo(renderer);

    state = SDL_GetKeyboardState(NULL);
    bool down = false;

    Screen screen = RUN;//TODO: cambiar a MAIN

    //Main Loop
    while(true)
    {
        SDL_RenderCopy(renderer, background, NULL, &rect_background);
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
                        down = PRESSED;
                        pollito->yvel = FALLING_CONSTANT;
                    }
                    if(!state[SDL_SCANCODE_SPACE] && down)
                    {
                        down = NOT_PRESSED;
                    }

                }
                pollito->logica();
                tubito->logica();
                if(collision(tubito->rect, pollito->point, pollito->radius) || collision(tubito->rect2, pollito->point, pollito->radius))
                {
                    screen = DEATH;
                    pollito->muerte();
                }
                break;

            case MAIN:
                //TODO: MAIN
                break;

            case PAUSE:
                //TODO: PAUSE
                break;

            case DEATH:
                SDL_RenderCopy(renderer, pollito->character, NULL, &pollito->rect);
                SDL_RenderCopy(renderer, tubito->tubodown, NULL, &tubito->rect);
                SDL_RenderCopy(renderer, tubito->tuboup, NULL, &tubito->rect2);
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

void restart(SDL_Rect *a, SDL_Rect *b, SDL_Rect *c)
{
    a->y = 250.0f;
    b->y = -300;
    b->x = 1280;
    c->y = 500;
    c->x = 1280;
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
