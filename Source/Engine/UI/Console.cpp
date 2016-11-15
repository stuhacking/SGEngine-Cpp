//
// Console Implementation
//
#include "../Engine.h"
#include <cstdio>
#include <cstdarg>

namespace sge {

Console console;

// -----------------------------------------------

void Console::Error (const char *msg) {
    fputs("ERROR: ", stderr);
    fprintf(stderr, "%s", msg);
}

void Console::Errorf (const char * const fmt, ...) {
    va_list args;
    va_start (args, fmt);
    fputs("ERROR: ", stderr);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

#ifndef NDEBUG

void Console::Debug (const char *msg) {
    fputs("DEBUG: ", stdout);
    fprintf(stdout, "%s", msg);
}

void Console::Debugf (const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    fputs("DEBUG: ", stdout);
    vfprintf(stdout, fmt, args);
    va_end(args);
}

#endif /* !NDEBUG */

} /* namespace sge */
