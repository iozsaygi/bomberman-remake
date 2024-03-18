#include "debugger.h"

int main() {
    debugger_log(TRACE, "This is trace message %d", 0);
    debugger_log(WARNING, "This is warning message %d", 1);
    debugger_log(CRITICAL, "This is critical message %d", 2);
    return 0;
}