#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <list>
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <iostream>

#include "../include/Bird.h"
#include "../include/Tubo.h"
#include "../include/ground.h"
#include "../include/Flower.h"
#include "../include/Fireworks.h"
#include "../include/Background.h"
#include "../include/ObjetoMovible.h"
#include "../include/CustomTexture.h"
#include "../include/RegularTexture.h"

#define TICK_INTERVAL 17
#define FALLING_CONSTANT -11.5

SDL_Event Event;
SDL_Window *window;
SDL_Texture *message;
SDL_Renderer *renderer;
SDL_Surface *surfaceMessage;
SDL_Color textcolor, colors[4];
Mix_Chunk *space_click_sound, *death_sound;
SDL_Rect message_rect, highscore_rect, flash, *chickenmain, *startrect, *mainexitrect, *restartrect, *deathexitrect, *scoresrect[3];

bool down = false;
const Uint8 *state;
float pollitomurioen;
static Uint32 next_time, now;
enum Screen {MAIN, PAUSE, DEATH, RUN};
int *counter, *mouse_x, *mouse_y, scores[3];

Screen screen;
Bird *pollito;
TTF_Font *font;
Flower *flower;
Fireworks *fireworks;
Background *background;
RegularTexture *texture;

std::list<ObjetoMovible*>objetos;

void restart();
void initrects();
void loadscores();
void printscores();
void updatescores();
void changeskin(int i);
Uint32 time_left(void);
bool clickin(SDL_Rect* rect);
bool collision(SDL_Rect a, SDL_Point b, int radius);
void renderSurface(std::string str, SDL_Rect* rect);

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

    if( Mix_OpenAudio( 22050, AUDIO_S16SYS/*MIX_DEFAULT_FORMAT*/, 2, 1024 ) == -1 )
        return 15;

    death_sound = Mix_LoadWAV("sound/death_sound.wav");
    space_click_sound = Mix_LoadWAV("sound/space_sound.wav");
    Mix_PlayChannel(1, Mix_LoadWAV("sound/background_music.ogg"), -1);

    if((window = SDL_CreateWindow("Flappy Pollito v1.0", 100, 100,
    1360, 720, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
        return 20;

    SDL_GL_SetSwapInterval(1);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
    objetos.push_back(new Flower(renderer));
    pollito = new Bird(renderer, texture);
    fireworks = new Fireworks(renderer, counter);

    TTF_Init();
    font = TTF_OpenFont("assets/text.ttf", 200);
    colors[0] = {255, 255, 255};
    colors[1] = {169, 231, 227};
    colors[2] = {0, 0, 0};
    colors[3] = colors[0];

    textcolor = colors[0];

    initrects();
    loadscores();

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
                        Mix_PlayChannel(2, space_click_sound, 0);
                    }
                    if(!state[SDL_SCANCODE_SPACE] && down)
                        down = false;
                }

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
                        updatescores();
                        Mix_PlayChannel(2, death_sound, 0);
                        screen = DEATH;
                    }
                    (*e)->logica();
                }
                renderSurface(patch::to_string(*counter), &message_rect);
                pollito->logica();
                fireworks->logica();
            break;

            case MAIN:
                SDL_RenderCopy(renderer, texture->mainmenu, NULL, &flash);
                SDL_RenderCopy(renderer, texture->chicken, NULL, chickenmain);
                printscores();
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
                renderSurface(patch::to_string(*counter), &message_rect);
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

void renderSurface(std::string str, SDL_Rect* rect)
{
    surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), textcolor);
    message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_RenderCopy(renderer, message, NULL, rect);
}

void printscores()
{
    for(int x = 0; x < 3; x++)
        renderSurface(patch::to_string(scores[x]), scoresrect[x]);
    renderSurface("Highscores", &highscore_rect);
}



void updatescores()
{
    for(int x = 0; x<3; x++)
    {
        if(scores[x] < *counter)
        {
            if(x==0)
            {
                scores[2] = scores[1];
                scores[1] = scores[0];
            }
            else if(x==1)
                scores[2] = scores[1];

            scores[x] = *counter;
            break;
        }
    }
    std::ofstream out("assets/highscores");
    out<<scores[0];
    out<<" ";
    out<<scores[1];
    out<<" ";
    out<<scores[2];
    out.close();
}

void loadscores()
{
    std::ifstream in("assets/highscores");
    int score;
    if(in.fail()){
        scores[0] = 15;
        scores[1] = 10;
        scores[2] = 5;
    }else{
        in>>score;
        scores[0] = score;
        in>>score;
        scores[1] = score;
        in>>score;
        scores[2] = score;
    }
    in.close();
    updatescores();
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
    objetos.push_back(new Flower(renderer));
    pollito = new Bird(renderer, texture);
}

void restart()
{
    objetos.clear();
    objetos.push_back(new Background(renderer, texture));
    objetos.push_back(new Tubo(renderer, texture, counter));
    objetos.push_back(new ground(renderer, texture));
    objetos.push_back(new Flower(renderer));
    pollito = new Bird(renderer, texture);
    *counter = 0;
    pollitomurioen = 0;
    screen = RUN;
}

void initrects()
{
    startrect = new SDL_Rect();
    restartrect = new SDL_Rect();
    chickenmain = new SDL_Rect();
    mainexitrect = new SDL_Rect();
    deathexitrect = new SDL_Rect();

    for(int x = 0; x < 3; x++)
        scoresrect[x] = new SDL_Rect();

    flash = {0, 0, 1360, 720};
    message_rect = {590, 5, 100, 100};
    highscore_rect = {990, 300, 300, 80};

    *startrect = {488, 305, 352, 145};
    *chickenmain = {185, 395, 76, 66};
    *restartrect = {520, 290, 300, 100};
    *mainexitrect = {488, 500, 352, 145};
    *deathexitrect = {520, 440, 300, 100};
    *scoresrect[0] = {1100, 380, 100, 100};
    *scoresrect[1] = {1100, 450, 100, 100};
    *scoresrect[2] = {1100, 520, 100, 100};
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
