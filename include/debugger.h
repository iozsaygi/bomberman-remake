#ifndef DEBUGGER_H
#define DEBUGGER_H

enum debugger_logLevel {
    CRITICAL,
    TRACE,
    WARNING
};

void debugger_log(enum debugger_logLevel logLevel, const char* message, ...);

#endif// !DEBUGGER_H