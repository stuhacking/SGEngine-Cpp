//
// Game Implementation
//
#include "Game.h"
#include <iostream>
#include <cstring>

// JSON Scene Keys.
static constexpr auto SHADERS_KEY = "shaders";
static constexpr auto OBJECTS_KEY = "objects";
static constexpr auto NAME_KEY = "name";

// View/Camera properties.
static Transform view;
static GLProjection proj{0.1f, 256.0f, 50.0f};

static float CAM_SPEED = 0.5f;

// Line drawing.
static DebugGraphics dGraph;

static GLSLProgram readShaderData (const json::Value &json) {
    assert(json.IsArray());
    GLSLProgram program;
    for (const auto &shaderFile : json.GetArray()) {
        if (shaderFile.IsString()) {
            program.AddSource(shaderFile.GetString());
        }
    }

    return program;
}

static Mesh readMeshData (const json::Value &json) {
    return meshFromObjDocument(json.GetString());
}

static Mesh readPrimitiveData (const json::Value &json) {
    assert(json.HasMember("type"));
    Mesh m;
    Vec3f size = Vec3f::ONE;
    Vec3f position = Vec3f::ZERO;

    if (json.HasMember("size")) {
        size = json::ReadVec3f(json["size"]);
    }

    if (json.HasMember("location")) {
        position = json::ReadVec3f(json["location"]);
    }

    if (strncmp("cube", json["type"].GetString(), 4) == 0) {
        m = Cube(position, size).ToMesh();
    } else if (strncmp("plane", json["type"].GetString(), 5) == 0) {
        m = Plane(position, size.xz()).ToMesh();
    }

    return m;
}

static Entity readObjectData (const json::Value &json) {
    assert(json.HasMember("shader") && json.HasMember("texture") && json.HasMember("transform"));
    Mesh m;

    if (json.HasMember("mesh")) {
        m = readMeshData(json["mesh"]);
    } else if (json.HasMember("primitive")) {
        m = readPrimitiveData(json["primitive"]);
    } else {
        console.Printf("WARNING: No drawable in object: %s\n", json[NAME_KEY].GetString());
    }

    Image i = Image(json["texture"].GetString());
    Transform t = json::ReadTransform(json["transform"]);

    return Entity(m, i, t, json["shader"].GetString());
}

/** Read a table of preset color values from a json file. */
static bool readSceneData (Game &game, const char * const filename) {
    JSONFile file = JSONFile(filename);
    const json::Document *d = file.GetRootDocument();

    if (!d->HasParseError()) {
        assert(d->HasMember(SHADERS_KEY));
        for (const auto &shaderDef : (*d)[SHADERS_KEY].GetObject()) {
            GLSLProgram program = readShaderData(shaderDef.value);
            game.AddShader(shaderDef.name.GetString(), program);
        }

        assert(d->HasMember(OBJECTS_KEY));
        for (const auto &objectDef : (*d)[OBJECTS_KEY].GetArray()) {
            Entity e = readObjectData(objectDef);
            game.AddEntity(e);
        }

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
        console.Print("ERROR: Failed to create scene.\n");
        return false;
    }

    for (auto &shader : m_shaders) {
        shader.second.Compile();

        if (!shader.second.IsCompiled()) {
            console.Printf("ERROR: Error compiling shader -- %s.\n", shader.first.c_str());
            return false;
        }
    }

    for (auto &e : m_objects) {
        e.mr.Compile();
        if (!e.mr.IsCompiled()) {
            console.Print("ERROR: Error compiling mesh.\n");
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
    GLSLProgram *shader;
    for (const auto &e : m_objects) {
        shader = BindShader(e.shader);
        shader->SetUniform("mvp", viewMat * e.transform.GetTransformationMatrix());
        e.texture.Bind();
        e.mr.Render();
    }

    dGraph.AddGrid(Vec3f::ZERO, 32, Color::FromHex("#DDD"));

    // Show World Axis
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 100.0f, 0.0f), Color::FromHex("#0000FF"));
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(100.0f, 0.0f, 0.0f), Color::FromHex("#FF0000"));
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 0.0f, 100.0f), Color::FromHex("#00FF00"));

    shader = BindShader("debug");
    shader->SetUniform("mvp", viewMat);
    dGraph.Render();

    dGraph.Clear();
}

GLSLProgram * Game::BindShader (const std::string &key) {
    auto shader = &(m_shaders[key]);

    shader->Bind();
    return shader;
}
