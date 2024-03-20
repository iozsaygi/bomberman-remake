#ifndef GAME_H
#define GAME_H

#include <SDL.h>

enum game_opResult {
    FAILURE,
    SUCCESS
};

struct game_platformContext {
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

extern struct game_platformContext game_platformContext;

enum game_opResult game_initializeDependencies();
enum game_opResult game_createPlatformContext(int width, int height, const char* title);

void game_clearPlatformContext();
void game_terminateDependencies();

#endif// !GAME_H