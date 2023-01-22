#ifndef _INCL_WRAPPER
#define _INCL_WRAPPER
#include <SDL2/SDL.h>
typedef struct SDL_struct_wrapper
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Wrapper;
#endif
