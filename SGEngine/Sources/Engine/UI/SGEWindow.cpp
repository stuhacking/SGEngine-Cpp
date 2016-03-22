/**
 * This wrapper will initialize SDL and also
 * set up an OpenGL context.
 */
#include "../Engine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

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
    SGEWindowSDL (const std::string &name, const u32 w, const u32 h,
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

static SGEWindowSDL sdlWindow = SGEWindowSDL("SGE Window", 800, 600);
SGEWindow *window = &sdlWindow;

// --------------------------------------------------------------------------

/**
 * Create an SDL Window with OpenGL context.
 */
SGEWindowSDL::SGEWindowSDL (const std::string &name, const u32 w, const u32 h,
                      const bool fullScreen) {
    m_initialized = false;
    m_name = name;
    m_width = w;
    m_height = h;

    DEBUG( console->Print(std::string(78, '*') + '\n'); );
    DEBUG( console->Print(" Initializing SDL...\n"); );
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to initialize SDL! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    u32 imgFlags = IMG_INIT_PNG & IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        std::cerr << "Failed to initialize SDL_Image! SDL_Error: " << IMG_GetError() << "\n";
        return;
    }

    u32 fullScreenFlag = (fullScreen) ? SDL_WINDOW_FULLSCREEN : 0;
    m_window = SDL_CreateWindow(m_name.c_str(),
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              m_width, m_height,
                              SDL_WINDOW_OPENGL | fullScreenFlag | SDL_WINDOW_SHOWN);
    if (nullptr == m_window) {
        std::cerr << "Failed to create SDL window! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    // Create GL Context
    DEBUG( console->Printf(" Request OpenGL Context [%d,%d]...\n", OGL_MAJOR, OGL_MINOR); );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OGL_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OGL_MINOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OGL_PROFILE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    auto glContext = SDL_GL_CreateContext(m_window);
    if (nullptr == glContext) {
        std::cerr << "Failed to create OpenGL context! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    DEBUG( console->Printf("  OpenGL Version: %s\n", glGetString(GL_VERSION)); );
    DEBUG( console->Printf("  OpenGL Vender: %s\n", glGetString(GL_VENDOR)); );
    DEBUG( console->Printf("  GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION)); );

    if (SDL_GL_SetSwapInterval(1) != 0) {
        std::cerr << "Warn: Unable to use VSync! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    // If using !Apple, need to initialize a GL Extension manager.
#ifndef __APPLE__
    DEBUG( console->Print(" Also initializing GL Extension Wrangler...\n"); );
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW Error! -- " << glewGetErrorString(err) << "\n";
        return;
    }
    if (!GLEW_VERSION_2_1) { // check that the machine supports the 2.1 API.
        std::cerr << "GLEW Version not supported!\n";
        return;
    }
#endif

    // Done initializing SDL, OpenGL. Now setup Render Options.
    // TODO Renderer class.

    // Default Cyan Clear color.
    SetClearColor(0.4f, 0.6f, 0.9f, 1.0f);

    //
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

    // Enabling Texturing
    glEnable(GL_TEXTURE_2D);

    m_initialized = true;

    DEBUG( console->Print(" Done initializing OpenGL.\n"); );
    DEBUG( console->Print(std::string(78, '*') + '\n'); );
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

} /* namespace sge */
