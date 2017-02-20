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

static GLuint matBuffer;
static GLuint lightBuffer;

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

struct matrix_data_t {
    Mat4f model;
    Mat4f view;
    Mat4f mvp;
};

struct light_data_t {
    int offsets[4];
    GLSLLight lights[16];
};

static matrix_data_t matrixData;
static light_data_t lightData;

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

    lightData.lights[0] = GLSLLight(Vec3f(0.12f, 0.01f, 0.02f),  Vec3f(0.0f, 4.0f, 0.0f),   Vec3f(0.0f, -1.0f, 0.0f), GLSLAttenuation(1.0f, 0.5f, 0.2f), 0.0f);
    lightData.lights[1] = GLSLLight(Vec3f(0.45f, 0.45f, 0.5f),     Vec3f(0.0f, 4.0f, 0.0f),   Vec3f(0.0f, -1.0f, 0.0f), GLSLAttenuation(1.0f, 0.5f, 0.2f), 0.0f);
    lightData.lights[2] = GLSLLight(Vec3f(0.08f, 0.08f, 0.07f),     Vec3f(0.0f, -4.0f, 0.0f),   Vec3f(0.0f, 1.0f, 0.0f), GLSLAttenuation(1.0f, 0.5f, 0.2f), 0.0f);
    lightData.lights[3] = GLSLLight(Vec3f(2.0f, 2.0f, 0.0f),     Vec3f(-3.0f, 7.0f, -5.0f),   Vec3f(0.0f, 0.0f, 0.0f), GLSLAttenuation(1.0f, 1.0f, 1.0f), 10.0f);
    lightData.lights[4] = GLSLLight(Vec3f(0.0f, 0.0f, 3.0f),     Vec3f(-10.0f, 4.0f, 0.0f),   Vec3f(0.0f, 0.0f, 0.0f), GLSLAttenuation(1.0f, 1.0f, 1.0f), 10.0f);
    lightData.offsets[0] = 1;
    lightData.offsets[1] = 3;
    lightData.offsets[2] = 3;
    lightData.offsets[3] = 5;

    glGenBuffers(1, &matBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, matBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(matrix_data_t), &matrixData, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &lightBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(light_data_t), &lightData, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

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
        for (auto &shader : m_shaders) {
            shader.second.Compile();
        }
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
    static double t;
    Entity *obj = &m_objects[1];
    obj->transform.RotateL(Vec3f::Y, TO_RADIANS(18.0f) * deltaSeconds); // One rotation in 20 seconds

    t += deltaSeconds;
    lightData.lights[3].position.y = sinf(t) * 5.0f + 5.0f;
    lightData.lights[4].position.x += 0.02f;
}

void Game::Render () {
    Mat4f viewMat = proj.GetPerspectiveProjection(m_width, m_height) *
        view.GetViewTransformationMatrix();

    glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
    GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    memcpy(p, &lightData, sizeof(light_data_t));
    glUnmapBuffer(GL_UNIFORM_BUFFER);

    // Custom drawing...
    GLSLProgram *shader;
    for (const auto &e : m_objects) {
        shader = BindShader(e.shader);

        // TODO [smh] Uniform buffer for transformations.
        // TODO [smh] Begin Frame...
        // Setup Matrix Data for Draw.
        matrixData.model = e.transform.GetTransformationMatrix();
        matrixData.view = view.GetViewTransformationMatrix();
        matrixData.mvp = viewMat * e.transform.GetTransformationMatrix();

        glBindBuffer(GL_UNIFORM_BUFFER, matBuffer);
        p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
        memcpy(p, &matrixData, sizeof(matrix_data_t));
        glUnmapBuffer(GL_UNIFORM_BUFFER);

        shader->BindUniformBuffer("MatrixBlock", matBuffer, 1);
        shader->BindUniformBuffer("LightingBlock", lightBuffer, 2);

        // TODO [smh] Uniform buffer for current material.
        shader->SetUniform("material.specIntensity", 0.75f);
        shader->SetUniform("material.specExponent", 0.3f);

        Image *i = imageManager.Get(e.texture);
        i->Bind();

        e.mr.Render();
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Show World Axis
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 100.0f, 0.0f), Color::FromHex("#0000FF"));
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(100.0f, 0.0f, 0.0f), Color::FromHex("#FF0000"));
    dGraph.AddEdge(Vec3f::ZERO, Vec3f(0.0f, 0.0f, 100.0f), Color::FromHex("#00FF00"));

    // Test Point Light positions
    dGraph.AddPoint(lightData.lights[3].position, 0.1f, Color(255, 255, 0));
    dGraph.AddPoint(lightData.lights[4].position, 0.1f, Color(0, 0, 255));

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
