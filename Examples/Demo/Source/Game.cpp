//
// Game Implementation
//
#include "Game.h"
#include "ImageManager.h"
#include <iostream>

// JSON Scene Keys.
static constexpr auto SHADERS_KEY = "shaders";
static constexpr auto OBJECTS_KEY = "objects";
static constexpr auto NAME_KEY = "name";

// View/Camera properties.
static Transform view;
static GLProjection proj{0.1f, 256.0f, 50.0f};

static float CAM_SPEED = 0.1f;

static ImageManager imageManager;

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
    assert(json.HasMember("shader") && json.HasMember("texture"));
    Mesh m;
    Transform t;

    if (json.HasMember("mesh")) {
        m = readMeshData(json["mesh"]);
    } else if (json.HasMember("primitive")) {
        m = readPrimitiveData(json["primitive"]);
    } else {
        console.Debugf("WARNING: No drawable in object: %s\n", json[NAME_KEY].GetString());
    }

    std::string imagePath = json["texture"].GetString();
    imageManager.Load(imagePath);

    if (json.HasMember("transform")) {
        t = json::ReadTransform(json["transform"]);
    }

    return Entity(MeshRenderer(m), imagePath, t, json["shader"].GetString());
}

/** Read a table of preset color values from a json file. */
static bool readSceneData (Game &game, const char * const filename) {
    JSONFile file(filename);
    const json::Document &d = *(file.GetRootDocument());

    if (!d.HasParseError()) {
        if (d.HasMember(SHADERS_KEY)) {
            for (const auto &shaderDef : d[SHADERS_KEY].GetObject()) {
                GLSLProgram program = readShaderData(shaderDef.value);
                game.AddShader(shaderDef.name.GetString(), program);
            }
        }

        if (d.HasMember(OBJECTS_KEY)) {
            for (const auto &objectDef : d[OBJECTS_KEY].GetArray()) {
                Entity e = readObjectData(objectDef);
                game.AddEntity(e);
            }
        }

        return true;
    }

    return false;
}

bool Game::Init () {
    if (!readSceneData(*this, "./data/scene.json")) {
        console.Errorf("Failed to create scene.\n");
        return false;
    }

    for (auto &shader : m_shaders) {
        shader.second.Compile();

        if (!shader.second.IsCompiled()) {
            console.Errorf("Error compiling shader -- %s.\n", shader.first.c_str());
            return false;
        }
    }

    for (auto &e : m_objects) {
        e.mr.Compile();
        if (!e.mr.IsCompiled()) {
            console.Errorf("Error compiling mesh.\n");
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

    if (Input::KeyReleased('r')) {
        imageManager.Reload();
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
            view.RotateL(Vec3f::X, -deltaPos.y * sensitivity);
        }

        if (rotY) {
            view.RotateW(Vec3f::Y, -deltaPos.x * sensitivity);
        }
    }
}

void Game::Update (double deltaSeconds) {
    Entity *obj = &m_objects[2];
    obj->transform.RotateL(Vec3f::Y, TO_RADIANS(18.0f) * deltaSeconds); // One rotation in 20 seconds
}

void Game::Render () {
    Mat4f viewMat = proj.GetPerspectiveProjection(m_width, m_height) *
        view.GetViewTransformationMatrix();

    // Custom drawing...
    GLSLProgram *shader;
    for (const auto &e : m_objects) {
        shader = BindShader(e.shader);
        shader->SetUniform("mvp", viewMat * e.transform.GetTransformationMatrix());
        //shader->SetUniform("view", view.GetViewTransformationMatrix());
        shader->SetUniform("model", e.transform.GetViewTransformationMatrix());
        shader->SetUniform("eyePos", view.position);

        Image *i = imageManager.Get(e.texture);
        i->Bind();

        e.mr.Render();
    }

    // Show World Axis
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 100.0f, 0.0f), Color::FromHex("#0000FF"));
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(100.0f, 0.0f, 0.0f), Color::FromHex("#FF0000"));
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 0.0f, 100.0f), Color::FromHex("#00FF00"));

    // Test Light positions
    dGraph.AddPoint(Vec3f(-3, 5, -5), 0.2f, Color(255, 255, 0));

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
