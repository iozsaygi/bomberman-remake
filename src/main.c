#include "debugger.h"
#include <SDL.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        debugger_log(CRITICAL, "Failed to initialize SDL with video subsystem, the reason was: %s", SDL_GetError());
        return -1;
    }

    SDL_Quit();
    return 0;
}