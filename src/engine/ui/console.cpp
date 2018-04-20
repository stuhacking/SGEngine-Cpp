//
// Console Implementation
//
#include "../engine.h"
#include <cstdio>
#include <cstdarg>

namespace sge {

Console gConsole;

// -----------------------------------------------

void Console::error (const char *msg) {
    fputs("ERROR: ", stderr);
    fprintf(stderr, "%s", msg);
}

void Console::errorf (const char *const fmt, ...) {
    va_list args;
    va_start (args, fmt);
    fputs("ERROR: ", stderr);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

#ifndef NDEBUG

void Console::debug (const char *msg) {
    fputs("DEBUG: ", stdout);
    fprintf(stdout, "%s", msg);
}

void Console::debugf (const char *const fmt, ...) {
    va_list args;
    va_start (args, fmt);
    fputs("DEBUG: ", stdout);
    vfprintf(stdout, fmt, args);
    va_end(args);
}

#endif /* !NDEBUG */

} /* namespace sge */
