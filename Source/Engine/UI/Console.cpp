//
// Console Implementation
//
#include "../Engine.h"
#include <cstdio>
#include <cstdarg>

namespace sge {

Console console;

// -----------------------------------------------

#ifndef NDEBUG

void Console::Print (const char *msg) {
    printf("%s", msg);
}

void Console::Printf (const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

#endif /* !NDEBUG */

} /* namespace sge */
