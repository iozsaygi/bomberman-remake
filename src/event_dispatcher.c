#include "event_dispatcher.h"
#include <SDL.h>

enum eventDispatcher_eventType eventDispatcher_handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return SHUTDOWN;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_SPACE) {
                    return KEY_DOWN_SPACE;
                } else if (event.key.keysym.sym == SDLK_w) {
                    return KEY_DOWN_W;
                } else if (event.key.keysym.sym == SDLK_a) {
                    return KEY_DOWN_A;
                } else if (event.key.keysym.sym == SDLK_s) {
                    return KEY_DOWN_S;
                } else if (event.key.keysym.sym == SDLK_d) {
                    return KEY_DOWN_D;
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return KEY_DOWN_ESCAPE;
                }
        }
    }

    return NONE;
}