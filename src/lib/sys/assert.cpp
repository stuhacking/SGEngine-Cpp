#include "assert.h"

#include <cstdio>

void assert_failed (const char *const file, const int line, const char *const expr) {
    fprintf(stderr, "ASSERTION FAILED: %s -- %s:%d\n", expr, file, line);
}
