/**
 * This wrapper will initialize SDL and also
 * set up an OpenGL context.
 */
#include "../Engine.h"

#include <SDL2/SDL_opengl.h>
#include <iostream>

#define OGL_MAJOR 3
#define OGL_MINOR 3
#define OGL_PROFILE SDL_GL_CONTEXT_PROFILE_CORE

namespace sge {

/**
 * Create an SDL Window with OpenGL context.
 */
SGEWindow::SGEWindow (const std::string &name, const u32 w, const u32 h, const bool fullScreen) {
    m_initialized = false;
    m_name = name;
    m_width = w;
    m_height = h;

    std::cout << string(78, '*') << "\n";
    std::cout << " Initializing SDL...\n";
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to initialize SDL! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    int imgFlags = IMG_INIT_PNG & IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        std::cerr << "Failed to initialize SDL_Image! SDL_Error: " << IMG_GetError() << "\n";
        return;
    }

    u32 fullScreenFlag = (fullScreen) ? SDL_WINDOW_FULLSCREEN : 0;
    window = SDL_CreateWindow(m_name.c_str(),
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              m_width, m_height,
                              SDL_WINDOW_OPENGL | fullScreenFlag | SDL_WINDOW_SHOWN);
    if (nullptr == window) {
        std::cerr << "Failed to create window! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    // Create GL Context
    std::cout << " Trying to Create OpenGL Context [" << OGL_MAJOR << "," << OGL_MINOR << "]...\n";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OGL_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OGL_MINOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OGL_PROFILE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    auto glContext = SDL_GL_CreateContext(window);
    if (nullptr == glContext) {
        std::cerr << "Failed to create OpenGL context! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    std::cout << "  OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "  OpenGL Vender: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "  GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

    if (SDL_GL_SetSwapInterval(1) != 0) {
        std::cerr << "Warn: Unable to use VSync! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    // If using !Apple, need to initialize a GL Extension manager.
#ifndef __APPLE__
    std::cout << " Also initializing GL Extension Wrangler...\n";
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
    SGEWindow::SetClearColor(0.4f, 0.6f, 0.9f, 1.0f);
    
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

    std::cout << " Done initializing OpenGL.\n";
    std::cout << string(78, '*') << "\n";
}

SGEWindow::~SGEWindow () {
    if (nullptr != window) {
        SDL_DestroyWindow(window);
    }

    IMG_Quit();
    SDL_Quit();
}

void SGEWindow::Update () const {
    SDL_GL_SwapWindow(window);
}

void SGEWindow::Delay (u32 period) const {
    SDL_Delay(period);
}

void SGEWindow::SetClearColor (const float r, const float g, const float b, const float a) const {
    glClearColor(r, g, b, a);
}

void SGEWindow::Clear () const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} /* namespace sge */
