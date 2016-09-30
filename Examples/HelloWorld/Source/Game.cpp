//
// Game Implementation
//
#include "Game.h"
#include "rapidjson/document.h"

#include <cstdio>
#include <iostream>
#include <vector>

using namespace rapidjson;

static Transform view;
static GLProjection proj{0.1f, 256.0f, 50.0f};

static float CAM_SPEED = 0.5f;

static u32 BLACK = 0;
static u32 DGRAY = 1;
static u32 LGRAY = 2;
static u32 RED = 3;
static u32 LRED = 4;
static u32 GREEN = 5;
static u32 LGREEN = 6;
static u32 BLUE = 7;
static u32 LBLUE = 8;
static u32 BROWN = 9;
static u32 MAGENTA = 10;
static u32 LMAGENTA = 11;
static u32 CYAN = 12;
static u32 LCYAN = 13;
static u32 YELLOW = 14;
static u32 WHITE = 15;

static std::vector<Color> colors;

/** Read contents of file in a go. */
static char * slurp (const char * const filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        std::cerr << "Error opening file: " << filename << "\n";
        return nullptr;
    }
    fseek(fp, 0, SEEK_END);
    size_t fileSize = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buf = new char[fileSize + 1];
    size_t readLength = fread(buf, 1, fileSize, fp);
    buf[readLength] = '\0';
    fclose(fp);

    return buf;
}

/** Parse out a color directive from json format { "color": [r, g, b] }. */
static Color parseColor (const Document &d, const char * const color) {
    assert(d.HasMember(color));
    const Value &docColor = d[color];

    return Color(docColor[0].GetInt(),
                 docColor[1].GetInt(),
                 docColor[2].GetInt());
}

/** Read a table of preset color values from a json file. */
static void readColorTable (const char * const filename) {
    char *buf = slurp(filename);
    if (buf) {
        Document d;

        if (d.ParseInsitu(buf).HasParseError()) {
            std::cerr << "Error parsing color table: " << filename << "\n";
            goto cleanup;
        }

        colors.reserve(16);
        colors.push_back(parseColor(d, "Black"));
        colors.push_back(parseColor(d, "DGray"));
        colors.push_back(parseColor(d, "LGray"));
        colors.push_back(parseColor(d, "Red"));
        colors.push_back(parseColor(d, "LRed"));
        colors.push_back(parseColor(d, "Green"));
        colors.push_back(parseColor(d, "LGreen"));
        colors.push_back(parseColor(d, "Blue"));
        colors.push_back(parseColor(d, "LBlue"));
        colors.push_back(parseColor(d, "Brown"));
        colors.push_back(parseColor(d, "Magenta"));
        colors.push_back(parseColor(d, "LMagenta"));
        colors.push_back(parseColor(d, "Cyan"));
        colors.push_back(parseColor(d, "LCyan"));
        colors.push_back(parseColor(d, "Yellow"));
        colors.push_back(parseColor(d, "White"));

        cleanup:
        delete[] buf;
    }
}

Game::Game (const u32 width, const u32 height) {
    m_width = width;
    m_height = height;
}

bool Game::Init () {
    readColorTable("./data/colors.json");
    if (colors.empty()) {
        std::cerr << "No colors loaded.\n";
        return false;
    }

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
            view.Rotate(Vec3f::X, -deltaPos.y * sensitivity);
        }

        if (rotY) {
            view.Rotate(Vec3f::Y, -deltaPos.x * sensitivity);
        }
    }
}

void Game::Update (double deltaSeconds) {
}

void Game::Render () {
    Mat4f proj_view = proj.GetPerspectiveProjection(m_width, m_height) *
        view.GetViewTransformationMatrix();

    // Custom drawing...
    m_objShader.Bind();
    for (const auto &e : m_objects) {
        m_objShader.SetUniform("mvp", proj_view * e.transform.GetTransformationMatrix());
        e.texture.Bind();
        e.mr.Render();
    }


    DebugGraphics dGraph = DebugGraphics();
    dGraph.AddGrid(Vec3f::ZERO, 16, colors[MAGENTA]);

    // Show World Axis
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 100.0f, 0.0f),
                   Color(0, 0, 255));
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(100.0f, 0.0f, 0.0f),
                   Color(255, 0, 0));
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 0.0f, 100.0f),
                   Color(0, 255, 0));

    m_debugShader.Bind();
    m_debugShader.SetUniform("mvp", proj_view);
    dGraph.Render();

    dGraph.Clear();
}
