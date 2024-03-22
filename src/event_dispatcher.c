#include "event_dispatcher.h"
#include <SDL.h>

enum eventDispatcher_eventType eventDispatcher_handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return SHUTDOWN;
        }
    }

    return NONE;
}