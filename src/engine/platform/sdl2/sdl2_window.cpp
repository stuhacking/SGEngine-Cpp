/**
 * This wrapper will initialize SDL and also
 * set up an OpenGL context.
 */
#include "../../engine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <memory>

static constexpr GLint kGlMajorVersion = 3;
static constexpr GLint kGlMinorVersion = 3;
static constexpr GLint kGlProfile = SDL_GL_CONTEXT_PROFILE_CORE;

namespace sge {


class SGEWindowSDL : public SGEWindow {
public:
    /**
     * Initialize an SGE Window using SDL2 as the UI backend and
     * SDL2 OpenGL for rendering context.
     */
    SGEWindowSDL (const char * const pTitle, const u32 pWidth, const u32 pHeight,
                  const bool pFullScreen = false);

    ~SGEWindowSDL ();

    virtual void update () const;

    virtual void delay (u32 period) const;

    virtual void clear () const;

private:
    SDL_Window *mWindow;
};


// --------------------------------------------------------------------------

/**
 * Create an SDL Window with OpenGL context.
 */
SGEWindowSDL::SGEWindowSDL (const char * const pTitle, const u32 pWidth, const u32 pHeight,
                            const bool pFullScreen) {
    mInitialized = false;
    mWidth = pWidth;
    mHeight = pHeight;
    SDL_version cmp, rt;

    SDL_VERSION(&cmp);
    SDL_GetVersion(&rt);

    gConsole.debug(
            "*********************************************************************\n");
    gConsole.debugf(
            "Initializing SDL... [Compiled (%d.%d.%d), Runtime (%d.%d.%d)]\n",
            cmp.major, cmp.minor, cmp.patch,
            rt.major, rt.minor, rt.patch);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        gConsole.errorf("Failed to initialize SDL! SDL_Error: %s\n",
                       SDL_GetError());
        return;
    }

    u32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    flags |= (pFullScreen) ? SDL_WINDOW_FULLSCREEN : 0;

    mWindow = SDL_CreateWindow(pTitle,
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                pWidth, pHeight,
                                flags);

    if (nullptr == mWindow) {
        gConsole.errorf("Failed to create SDL window! SDL_Error: %s\n",
                       SDL_GetError());
        return;
    }

    // Create gl Context
    gConsole.debugf("Create OpenGL Context [%d,%d]...\n", kGlMajorVersion,
                   kGlMinorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, kGlMajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, kGlMinorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, kGlProfile);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    auto glContext = SDL_GL_CreateContext(mWindow);

    if (nullptr == glContext) {
        gConsole.errorf("Failed to create OpenGL context! SDL_Error: %s\n",
                       SDL_GetError());
        return;
    }

    gConsole.debugf("OpenGL: %s [%s]\n",
                   glGetString(GL_VERSION),
                   glGetString(GL_VENDOR));
    gConsole.debugf("OpenGL Shading Language: %s\n",
                   glGetString(GL_SHADING_LANGUAGE_VERSION));

    if (SDL_GL_SetSwapInterval(1) != 0) {
        gConsole.errorf("Unable to use VSync! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Apple's OpenGL framework provides an extension manager. If not using Apple,
    // initialize GLEW.
#ifndef __APPLE__
    gConsole.debug("Initializing gl Extension Wrangler...\n");
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        gConsole.errorf("GLEW Error! -- %s\n", glewGetErrorString(err));
        return;
    }
    if (!GLEW_VERSION_2_1) { // check that the machine supports the 2.1 API.
        gConsole.error("GLEW Version not supported. Requires 2.1.\n");
        return;
    }
#endif

    // Done initializing SDL, OpenGL. Now setup render Options.
    // TODO Split out Window/Platform initialization from Rendering initialization.

    // Ugly purple default colour. If you see this, you're not filling the
    // viewport.
    glClearColor(0.8f, 0.2f, 0.8f, 1.0f);

    // Turn on a bunch of gl options.
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
    SDL_GetWindowSize(mWindow, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    gConsole.debug("OpenGL Initialized.\n");
    gConsole.debug(
            "*********************************************************************\n");

    mInitialized = true;
}

SGEWindowSDL::~SGEWindowSDL () {
    if (nullptr != mWindow) {
        SDL_DestroyWindow(mWindow);
    }

    SDL_Quit();
}

void SGEWindowSDL::update () const {
    SDL_GL_SwapWindow(mWindow);
}

void SGEWindowSDL::delay (u32 period) const {
    SDL_Delay(period);
}

void SGEWindowSDL::clear () const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// --------------------------------------------------------------------------

/** Global Application Window */
static std::unique_ptr<SGEWindowSDL> sdlWindow;
SGEWindow *gWindow;

/**
 * Initialize the context for a 3D application.
 */
bool initSGEApplication (const char *const pTitle, const u32 pWidth,
                         const u32 pHeight,
                         const bool pFullScreen) {
    sdlWindow = std::make_unique<SGEWindowSDL>(pTitle, pWidth, pHeight, pFullScreen);
    gWindow = sdlWindow.get();

    return gWindow->isInitialized();
}

} /* namespace sge */
