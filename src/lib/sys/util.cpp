/**
 * \file util.cpp
 *
 * Created: 10 Nov 2017
 *
 * Copyright (c) 2017 Stuart Hacking
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 */
#include "util.h"

#include <cstdlib>
#include <cstdio>

char *progName = nullptr;
void (*quit_aux)() = nullptr;
void (*log_aux)(const char *const msg) = nullptr;

void quit (const char *const msg) {

    if (nullptr != quit_aux) {
        quit_aux();
    }

    if (nullptr == msg) {
        exit(EXIT_SUCCESS);
    }

    logError(msg);
    exit(EXIT_FAILURE);
}

void logError (const char *const msg) {

    if (nullptr != progName) {
        fprintf(stderr, "%s: %s\n", progName, msg);
    } else {
        fprintf(stderr, "%s\n", msg);
    }
}
