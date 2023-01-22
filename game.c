#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "wrapper.h"

const int Y_TRAVEL = 6;
const int X_TRAVEL = 3;

void destroy_SDL_Components(SDL_Wrapper *wrapper, SDL_Rect *rect, SDL_Rect *ball)
{
    SDL_DestroyWindow(wrapper->window);
    SDL_DestroyRenderer(wrapper->renderer);
    SDL_Quit();
    free(wrapper);
    free(rect);
    free(ball);
}

void init_Items(SDL_Wrapper *wrapper, SDL_Rect *rect, SDL_Rect *ball)
{
    SDL_RenderClear(wrapper->renderer);
    SDL_SetRenderDrawColor(wrapper->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(wrapper->renderer, rect);
    SDL_SetRenderDrawColor(wrapper->renderer, 140, 40, 140, 255);
    SDL_RenderFillRect(wrapper->renderer, ball);
    SDL_SetRenderDrawColor(wrapper->renderer, 0, 0, 0, 255);
    SDL_RenderPresent(wrapper->renderer);
}

void handle_Event(SDL_Wrapper *wrapper, const Uint8 *key, SDL_Rect *rect, SDL_Rect *ball)
{
    if (key[SDL_SCANCODE_J])
    {
        rect->y += Y_TRAVEL;
    }
    if (key[SDL_SCANCODE_K])
    {
        rect->y -= Y_TRAVEL;
    }
    if (key[SDL_SCANCODE_H])
    {
        rect->x -= X_TRAVEL;
    }
    if (key[SDL_SCANCODE_L])
    {
        rect->x += X_TRAVEL;
    }

    if (SDL_HasIntersection(rect, ball) == SDL_TRUE)
    {
        int x_no_bounds = rand();
        int y_no_bounds = rand();
        ball->x = (x_no_bounds - (x_no_bounds % 80)) % 1600;
        ball->y = (y_no_bounds - (y_no_bounds % 90)) % 900;
    }
    init_Items(wrapper, rect, ball);
}

void init_Seed()
{
    srandom(time(NULL)); // Initialization, should only be called once.
}
void game_Loop(SDL_Wrapper *wrapper)
{
    int FPS = 144;
    int FrameStartTimeMs = 0;
    float speed = 5.0 / FPS;
    init_Seed();
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));
    rect->x = 800;
    rect->y = 450;
    rect->w = 80;
    rect->h = 90;
    SDL_Rect *ball = malloc(sizeof(SDL_Rect));
    ball->x = 960;
    ball->y = 540;
    ball->w = 80;
    ball->h = 90;
    init_Items(wrapper, rect, ball);
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    SDL_Event e;
    int quit = 1;
    while (quit)
    {

        FrameStartTimeMs = SDL_GetTicks();

        if (SDL_PollEvent(&e))
        {

            if (e.type == SDL_QUIT)
            {
                printf("quit");
                quit = 0;
            }
        }
        handle_Event(wrapper, keystate, rect, ball);
        while (SDL_GetTicks() - FrameStartTimeMs < 1000 / FPS)
            ;
    }

    destroy_SDL_Components(wrapper, rect, ball);
}
