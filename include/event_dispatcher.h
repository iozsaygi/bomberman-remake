#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

enum eventDispatcher_eventType {
    NONE,
    SHUTDOWN
};

enum eventDispatcher_eventType eventDispatcher_handleEvents();

#endif// !EVENT_DISPATCHER