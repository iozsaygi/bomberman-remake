#include "game.h"
#include "debugger.h"

struct game_platformContext game_platformContext;

enum game_opResult game_initializeDependencies() {
    // Try to initialize SDL. Use even more subsystems if required.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        debugger_log(CRITICAL, "Failed to initialize SDL, the reason was: %s", SDL_GetError());
        return FAILURE;
    }

    debugger_log(TRACE, "Successfully initialized game dependencies");
    return SUCCESS;
}

enum game_opResult game_createPlatformContext(int width, int height, const char* title, int targetFrameRate) {
    game_platformContext.width = width;
    game_platformContext.height = height;
    game_platformContext.targetFrameRate = targetFrameRate;

    game_platformContext.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (game_platformContext.window == NULL) {
        debugger_log(CRITICAL, "Failed to create window context, the reason was: %s", SDL_GetError());
        return FAILURE;
    }

    game_platformContext.renderer = SDL_CreateRenderer(game_platformContext.window, -1, 0);
    if (game_platformContext.renderer == NULL) {
        debugger_log(CRITICAL, "Failed to create renderer context, the reason was: %s", SDL_GetError());
        return FAILURE;
    }

    debugger_log(TRACE, "Successfully created platform context");
    return SUCCESS;
}

void game_clearPlatformContext() {
    SDL_DestroyRenderer(game_platformContext.renderer);
    SDL_DestroyWindow(game_platformContext.window);
    debugger_log(TRACE, "Successfully cleared platform context");
}

void game_terminateDependencies() {
    SDL_Quit();
    debugger_log(TRACE, "Successfully terminated initialized game dependencies");
}