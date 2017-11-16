/**
 * \file util.h
 *
 * Created: 10 Nov 2017
 *
 * Copyright (c) 2017 Stuart Hacking
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 */
#ifndef __SGE_UTIL_H
#define __SGE_UTIL_H

extern char* progName;

/** Redefinable quit hook. */
extern void (*quit_aux) ();

/** Redefinable log hook. */
extern void (*log_aux) (const char *const msg);

/** Quit with optional error message. */
void quit (const char *const msg = nullptr);

/** Log an error message. */
void logError (const char *const msg);

#endif /* __SGE_UTIL_H */
