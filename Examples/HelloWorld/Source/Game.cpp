//
// Game Implementation
//
#include "Game.h"

#include <iostream>

static Transform view;
static GLProjection proj{0.1f, 256.0f, 50.0f};

static float CAM_SPEED = 0.5f;

Game::Game (const u32 width, const u32 height) {
    m_width = width;
    m_height = height;
}

bool Game::Init () {
    m_objShader = GLSLProgram()
        .AddSource("./data/shader/obj.vs")
        .AddSource("./data/shader/obj.fs");
    m_objShader.Compile();

    if (!m_objShader.IsCompiled()) {
        std::cerr << "Error in Object Shader Compilation.\n";
        return false;
    }

    m_debugShader = GLSLProgram()
        .AddSource("./data/shader/debug.vs")
        .AddSource("./data/shader/debug.fs");
    m_debugShader.Compile();

    if (!m_debugShader.IsCompiled()) {
        std::cerr << "Error in Debug Shader Compilation.\n";
        return false;
    }

    // Test Object
    Mesh m = meshFromObjDocument("./data/HelloWorld.obj");
    Image i = Image("./data/HelloWorld_Tex.png");

    m_objects.emplace_back(m, i, Transform());

    for (auto &e : m_objects) {
        e.mr.Compile();
        if (!e.mr.IsCompiled()) {
            std::cerr << "Error compiling mesh.\n";
            return false;
        }
    }

    // Emulate a camera/view transform
    view = Transform();
    view.position = Vec3f(0.0f, 3.0f, 18.0f);

    return true;
}

void Game::Input () {

    if (Input::KeyDown(']')) {
        proj.fov += 1.0f;
    }
    if (Input::KeyDown('[')) {
        proj.fov -= 1.0f;
    }

    if (Input::KeyDown('a')) {
        view.position += view.Right() * -CAM_SPEED;
    }
    if (Input::KeyDown('d')) {
        view.position += view.Right() * CAM_SPEED;
    }
    if (Input::KeyDown('w')) {
        view.position += view.Forward() * -CAM_SPEED;
    }
    if (Input::KeyDown('s')) {
        view.position += view.Forward() * CAM_SPEED;
    }

    if (Input::MousePressed(1) && !Input::KeyDown(Input::Key::LShift)) {
        Input::LockMouse();
    }

    if (Input::MousePressed(1) && Input::KeyDown(Input::Key::LShift)) {
        Input::ReleaseMouse();
    }

    float sensitivity = 0.01f;
    if (Input::MouseLocked()) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        Vec2f deltaPos = Input::GetMouseDelta();

        bool rotX = deltaPos.y != 0;
        bool rotY = deltaPos.x != 0;

        if (rotX) {
            view.Rotate(VEC3F_X, -deltaPos.y * sensitivity);
        }

        if (rotY) {
            view.Rotate(VEC3F_Y, -deltaPos.x * sensitivity);
        }
    }
}

void Game::Update (double deltaSeconds) {
}

void Game::Render () {
    Matrix4 proj_view = proj.GetPerspectiveProjection(m_width, m_height) *
        view.GetViewTransformationMatrix();

    // Custom drawing...
    m_objShader.Bind();
    for (const auto &e : m_objects) {
        m_objShader.SetUniform("mvp", proj_view * e.transform.GetTransformationMatrix());
        e.texture.Bind();
        e.mr.Render();
    }


    DebugGraphics dGraph = DebugGraphics();
    dGraph.AddGrid(VEC3F_ZERO, 16, Color(255, 255, 255, 80));

    // Show World Axis
    dGraph.AddEdge(VEC3F_ZERO, Vec3f(0.0f, 100.0f, 0.0f),
                   Color(0, 0, 255));
    dGraph.AddEdge(VEC3F_ZERO, Vec3f(100.0f, 0.0f, 0.0f),
                   Color(255, 0, 0));
    dGraph.AddEdge(VEC3F_ZERO, Vec3f(0.0f, 0.0f, 100.0f),
                   Color(0, 255, 0));

    m_debugShader.Bind();
    m_debugShader.SetUniform("mvp", proj_view);
    dGraph.Render();

    dGraph.Clear();
}
