//
// Console Implementation
//
#include "../Engine.h"
#include <cstdio>
#include <cstdarg>

/**
 * Console class to replace simple standard output.
 */
class TextConsole : public Console {
public:
    void Print (const std::string &msg);

    void Printf (const std::string &fmt, ...);
};

static TextConsole textConsole;
Console *console = &textConsole;

// -----------------------------------------------

void TextConsole::Print (const std::string &msg) {
    printf("%s", msg.c_str());
}

void TextConsole::Printf (const std::string &fmt, ...) {
    va_list args;
    va_start (args, fmt);
    vprintf(fmt.c_str(), args);
    va_end(args);
}
