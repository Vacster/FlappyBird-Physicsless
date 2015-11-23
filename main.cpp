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
SDL_Texture *background,*mip, *mip2;
SDL_Texture *righty1, *lefty1, *up1, *down1, *righty2, *lefty2, *up2, *down2;
SDL_Rect rect_background,mir, mir2;
Mix_Music *music = NULL;
bool one = true;
int frames = 0;
double speed = 5;
static Uint32 next_time;

using namespace std;

//Que corra a la misma velocidad en diferentes computadoras
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

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    //Que corra a la misma velocidad en diferentes computadoras
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int xvel = 0, yvel = 0, xvel2 = 0, yvel2 = 0;
    next_time = SDL_GetTicks() + TICK_INTERVAL;

    Bird* pollito = new Bird(renderer);
    Tubo* tubito = new Tubo(renderer);

    state = SDL_GetKeyboardState(NULL);
    bool down = false;
    //Main Loop
    while(true)
    {
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
        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        pollito->logica();
        tubito->logica();
        SDL_RenderPresent(renderer);

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }

	return 0;
}
