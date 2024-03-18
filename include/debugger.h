#ifndef DEBUGGER_H
#define DEBUGGER_H

enum log_level {
    CRITICAL,
    TRACE,
    WARNING
};

void debugger_log(enum log_level logLevel, const char* message, ...);

#endif// !DEBUGGER_H