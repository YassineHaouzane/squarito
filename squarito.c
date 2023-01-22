#include <SDL2/SDL.h>
#include <stdio.h>
#include "game.h"
#include "wrapper.h"

const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = 1600;

SDL_Wrapper *init_SDL()
{
  SDL_Window *pWindow;
  SDL_Renderer *renderer;

  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    fprintf(stderr, "Failed to initialize SDL's resources (%s)\n", SDL_GetError());
    return NULL;
  }

  {

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_RESIZABLE, &pWindow, &renderer))
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    }
    else
    {
      SDL_Wrapper *res = malloc(sizeof(SDL_Wrapper));
      res->window = pWindow;
      res->renderer = renderer;
      return res;
    }
  }

  SDL_Quit();
  return NULL;
}

int main(int argc, char **argv)
{
  SDL_Wrapper *wrapper = init_SDL();
  if (wrapper)
  {
    game_Loop(wrapper);
  }
  return 0;
}
