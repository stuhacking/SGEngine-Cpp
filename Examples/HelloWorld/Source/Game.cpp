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

static DebugGraphics dGraph;
static int frame{0};

static Transform boxTransform;

/** Read contents of file in one go. */
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

/** Read a table of preset color values from a json file. */
static bool readSceneData (Game &game, const char * const filename) {
    char *buf = slurp(filename);
    if (buf) {
        Document d;

        if (d.ParseInsitu(buf).HasParseError()) {
            std::cerr << "Error parsing color table: " << filename << "\n";
            delete[] buf;
            return false;
        }

        assert(d.HasMember("shaders"));
        for (auto &shaderDef : d["shaders"].GetObject()) {
            assert(shaderDef.value.IsArray());
            GLSLProgram program;
            for (auto &shaderFile : shaderDef.value.GetArray()) {
                program.AddSource(shaderFile.GetString());
            }

            game.AddShader(shaderDef.name.GetString(), program);
        }

        delete[] buf;
        return true;
    }

    return false;
}

Game::Game (const u32 width, const u32 height) {
    m_width = width;
    m_height = height;
}

bool Game::Init () {
    if (!readSceneData(*this, "./data/scene.json")) {
        std::cerr << "Failed to create scene.\n";
        return false;
    }

    for (auto &shader : m_shaders) {
        shader.second.Compile();

        if (!shader.second.IsCompiled()) {
            std::cerr << "Error in Shader Compilation.\n";
            return false;
        }
    }

    // Test Object
    Mesh m = meshFromObjDocument("./data/HelloWorld.obj");
    Image i = Image("./data/HelloWorld_Tex.png");

    m_objects.emplace_back(m, i, Transform());

    m = Cube(Vec3f::ZERO, 1.0f).ToMesh();
    i = Image("./data/crate.png");

    m_objects.emplace_back(m, i, Transform(Vec3f(5.0f, 0.5f, 2.0f)));

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
    Entity *box = &m_objects[1];
    box->transform.Rotate(Vec3f::Y, 0.01f);
}

void Game::Render () {
    Mat4f viewMat = proj.GetPerspectiveProjection(m_width, m_height) *
        view.GetViewTransformationMatrix();

    // Custom drawing...
    auto shader = BindShader("obj");
    for (const auto &e : m_objects) {
        shader->SetUniform("mvp", viewMat * e.transform.GetTransformationMatrix());
        e.texture.Bind();
        e.mr.Render();
    }

    // Draw random walk.
    static Vec3f vec;
    Vec3f newVec = Vec3f::Random(++frame) * 0.2f + vec;
    dGraph.AddEdge(vec, newVec, Color::FromHex("#FFFF00"));
    vec = newVec;

    //dGraph.AddGrid(Vec3f::ZERO, 32, colors[MAGENTA]);

    // Show World Axis
    //dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 100.0f, 0.0f),
    //               colors[BLUE]);
    //dGraph.AddEdge(Vec3f::ZERO, Vec3f(100.0f, 0.0f, 0.0f),
    //               colors[RED]);
    //dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 0.0f, 100.0f),
    //               colors[GREEN]);

    shader = BindShader("debug");
    shader->SetUniform("mvp", viewMat);
    dGraph.Render();

    //dGraph.Clear();
}

GLSLProgram * Game::BindShader (const std::string &key) {
    auto shader = &(m_shaders[key]);

    shader->Bind();
    return shader;
}
