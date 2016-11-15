/**
 * This wrapper will initialize SDL and also
 * set up an OpenGL context.
 */
#include "../../Engine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <memory>

#define OGL_MAJOR 3
#define OGL_MINOR 3
#define OGL_PROFILE SDL_GL_CONTEXT_PROFILE_CORE

namespace sge {


class SGEWindowSDL : public SGEWindow {
public:
    /**
     * Initialize an SGE Window using SDL2 as the UI backend and
     * SDL2 OpenGL for rendering context.
     */
    SGEWindowSDL (const char * const name, const u32 w, const u32 h,
                  const bool fullScreen = false);

    ~SGEWindowSDL ();

    virtual void Update () const;

    virtual void Delay (const u32 period) const;

    virtual void SetClearColor (const float r, const float g, const float b,
                                const float a = 1.0f) const;

    virtual void Clear () const;

private:
    SDL_Window *m_window;
};


// --------------------------------------------------------------------------

/**
 * Create an SDL Window with OpenGL context.
 */
SGEWindowSDL::SGEWindowSDL (const char * const name, const u32 w, const u32 h,
                            const bool fullScreen) {
    m_initialized = false;
    m_name = name;
    m_width = w;
    m_height = h;

    console.Debug("Initializing SDL...\n");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        console.Errorf("Failed to initialize SDL! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    u32 imgFlags = IMG_INIT_PNG & IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        console.Errorf("Failed to initialize SDL_Image! SDL_Error: %s\n", IMG_GetError());
        return;
    }

    u32 fullScreenFlag = (fullScreen) ? SDL_WINDOW_FULLSCREEN : 0;
    m_window = SDL_CreateWindow(m_name.c_str(),
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                m_width, m_height,
                                SDL_WINDOW_OPENGL | fullScreenFlag | SDL_WINDOW_SHOWN);
    if (nullptr == m_window) {
        console.Errorf("Failed to create SDL window! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Create GL Context
    console.Debugf(" Request OpenGL Context [%d,%d]...\n", OGL_MAJOR, OGL_MINOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OGL_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OGL_MINOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OGL_PROFILE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    auto glContext = SDL_GL_CreateContext(m_window);
    if (nullptr == glContext) {
        console.Errorf("Failed to create OpenGL context! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    console.Debugf("  OpenGL Version: %s\n", glGetString(GL_VERSION));
    console.Debugf("  OpenGL Vender: %s\n", glGetString(GL_VENDOR));
    console.Debugf("  GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    if (SDL_GL_SetSwapInterval(1) != 0) {
        console.Errorf("Unable to use VSync! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // If using !Apple, need to initialize a GL Extension manager.
#ifndef __APPLE__
    console.Debug(" Also initializing GL Extension Wrangler...\n");
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        console.Errorf("GLEW Error! -- %s\n", glewGetErrorString(err));
        return;
    }
    if (!GLEW_VERSION_2_1) { // check that the machine supports the 2.1 API.
        console.Error("GLEW Version not supported. Requires 2.1.\n");
        return;
    }
#endif

    // Done initializing SDL, OpenGL. Now setup Render Options.
    // TODO Split out Window/Platform initialisation from Rendering initialisation.

    // Ugly default colour.
    SetClearColor(0.8f, 0.2f, 0.8f, 1.0f);

    // Turn on a bunch of GL options.
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Enable Backface Culling.
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Enable Depth Testing.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);

    // Enable transparent textures.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_CLAMP);

    // For now, just stretch the renderer
    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    m_initialized = true;

    console.Debug("Done initializing OpenGL.\n");
}

SGEWindowSDL::~SGEWindowSDL () {
    if (nullptr != m_window) {
        SDL_DestroyWindow(m_window);
    }

    IMG_Quit();
    SDL_Quit();
}

void SGEWindowSDL::Update () const {
    SDL_GL_SwapWindow(m_window);
}

void SGEWindowSDL::Delay (u32 period) const {
    SDL_Delay(period);
}

void SGEWindowSDL::SetClearColor (const float r, const float g, const float b, const float a) const {
    glClearColor(r, g, b, a);
}

void SGEWindowSDL::Clear () const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// --------------------------------------------------------------------------

/** Global Application Window */
static std::unique_ptr<SGEWindowSDL> sdlWindow;
SGEWindow *window;

/**
 * Initialize the context for a 3D application.
 */
bool InitSGEApplication (const char * const name, const u32 width, const u32 height,
                         const bool fullScreen) {
    sdlWindow = std::make_unique<SGEWindowSDL>(name, width, height, fullScreen);
    window = sdlWindow.get();

    return window->IsInitialized();
}

} /* namespace sge */
