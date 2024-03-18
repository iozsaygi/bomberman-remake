#include "debugger.h"
#include <stdarg.h>
#include <stdio.h>

void debugger_log(enum log_level logLevel, const char* message, ...) {
    va_list args;
    const char* tag = NULL;

    switch (logLevel) {
        case CRITICAL:
            tag = "[CRITICAL]";
            break;
        case TRACE:
            tag = "[TRACE]";
            break;
        case WARNING:
            tag = "[WARNING]";
            break;
    }

    printf("%s ", tag);
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
}