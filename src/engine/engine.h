/*---  Engine.h - SGE Engine Library Header  -----------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 */
#ifndef __SGE_ENGINE_H
#define __SGE_ENGINE_H

#ifdef __APPLE__
 #include <OpenGL/gl3.h>
 #include <SDL2_image/SDL_image.h>
#else
 #include <GL/glew.h>
 #include <GL/gl.h>
 #include <SDL2/SDL_image.h>
#endif

// --------------------------------------------------------------------------

#include "lib.h"

// Useful macro for specifying buffer locations in gl calls.
#define BUFFER_OFFSET(a) (GLvoid*)((a) * sizeof(GLfloat))

#include "data/jsonfile.h"
#include "ui/console.h"

#include "gl/glsllight.h"
#include "gl/glslshader.h"
#include "gl/glslprogram.h"
#include "gl/glprojection.h"

#include "image/image.h"

#include "model/obj.h"

#include "render/meshrenderer.h"
#include "render/debuggraphics.h"

#include "ui/sgewindow.h"
#include "ui/input.h"

#endif /* __SGE_H */
