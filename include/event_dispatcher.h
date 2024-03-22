#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

enum eventDispatcher_eventType {
    // Engine events.
    NONE,
    SHUTDOWN,

    // Input related events.
    KEY_DOWN_W,
    KEY_DOWN_A,
    KEY_DOWN_S,
    KEY_DOWN_D,
    KEY_DOWN_SPACE,
    KEY_DOWN_ESCAPE
};

enum eventDispatcher_eventType eventDispatcher_handleEvents();

#endif// !EVENT_DISPATCHER_H