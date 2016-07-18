/*---  Engine.h - SGE Engine Library Header  -----------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 */
#ifndef __SGENGINE_ENGINE_H_
#define __SGENGINE_ENGINE_H_

#ifdef __APPLE__
 #include <OpenGL/gl3.h>
 #include <SDL2_image/SDL_image.h>
#else
 #include <GL/glew.h>
 #include <GL/gl.h>
 #include <SDL2/SDL_image.h>
#endif

// --------------------------------------------------------------------------

#include "Lib.h"

// Useful macro for specifying buffer locations in GL calls.
#define BUFFER_OFFSET(a) (GLvoid*)((a) * sizeof(GLfloat))

#include "UI/Console.h"

#include "GL/GLSLShader.h"
#include "GL/GLSLProgram.h"
#include "GL/GLProjection.h"

#include "Image/Image.h"

#include "Model/Obj.h"

#include "Render/MeshRenderer.h"
#include "Render/DebugGraphics.h"

#include "UI/SGEWindow.h"
#include "UI/Input.h"

#endif /* __SGENGINE_H_ */
