//
// Game Implementation
//
#include "game.h"
#include "imagemanager.h"
#include <iostream>

// JSON Scene Keys.
static constexpr auto kShadersKey = "shaders";
static constexpr auto kObjectsKey = "objects";
static constexpr auto kNameKey    = "name";

// View/Camera properties.
static Transform view;
static GLProjection proj{0.1f, 256.0f, 50.0f};

static float camSpeed = 0.1f;

static GLuint matBuffer;         /**< Temporary material buffer Id. */
static GLuint lightBuffer;       /**< Temporary light buffer Id. */

static ImageManager imageManager; /**< Temporary Image Manager. */
static DebugGraphics debugGfx;   /**< Debug Line Drawing. */

/** Parse shader data from json file. */
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

/** Parse mesh data from json file. */
static Mesh readMeshData (const json::Value &json) {
    return meshFromObjDocument(json.GetString());
}

/** Parse primitive object data from json file. */
static Mesh readPrimitiveData (const json::Value &json) {
    assert(json.HasMember("type"));
    Mesh m;
    Vec3f size = Vec3f_One;
    Vec3f position = Vec3f_Zero;

    if (json.HasMember("size")) {
        size = json::readVec3f(json["size"]);
    }

    if (json.HasMember("location")) {
        position = json::readVec3f(json["location"]);
    }

    if (strncmp("cube", json["type"].GetString(), 4) == 0) {
        m = Cube(position, size).toMesh();
    } else if (strncmp("plane", json["type"].GetString(), 5) == 0) {
        m = Plane(position, size.xz()).toMesh();
    }

    return m;
}

/** Parse material data from json file. */
static Material readMaterialData (const json::Value &json) {
    Material m = {0.0f, 0.0f};

    if (json.HasMember("specIntensity")) {
        m.specIntensity = json["specIntensity"].GetFloat();
    }
    if (json.HasMember("specExponent")) {
        m.specIntensity = json["specExponent"].GetFloat();
    }

    return m;
}

/** Parse Object (entity) data from json file. */
static Entity readObjectData (const json::Value &json) {
    assert(json.HasMember("shader"));
    Mesh m;
    Transform t;
    Material mat = {0.0f, 0.0f};

    if (json.HasMember("mesh")) {
        m = readMeshData(json["mesh"]);
    } else if (json.HasMember("primitive")) {
        m = readPrimitiveData(json["primitive"]);
    } else {
        gConsole.debugf("WARNING: No drawable in object: %s\n",
                       json[kNameKey].GetString());
    }

    std::string imagePath = "";
    if (json.HasMember("texture")) {
        imagePath = json["texture"].GetString();
        imageManager.load(imagePath);
    }

    if (json.HasMember("material")) {
        mat = readMaterialData(json["material"]);
    }

    if (json.HasMember("transform")) {
        t = json::readTransform(json["transform"]);
    }

    return Entity(t, MeshRenderer(m), mat, imagePath, json["shader"].GetString());
}

/** Read a table of preset color values from a json file. */
static bool readSceneData (Game &game, const char * const filename) {
    JSONFile file(filename);
    const json::Document &d = *(file.rootDocument());

    if (!d.HasParseError()) {
        if (d.HasMember(kShadersKey)) {
            for (const auto &shaderDef : d[kShadersKey].GetObject()) {
                GLSLProgram program = readShaderData(shaderDef.value);
                game.addShader(shaderDef.name.GetString(), program);
            }
        }

        if (d.HasMember(kObjectsKey)) {
            for (const auto &objectDef : d[kObjectsKey].GetArray()) {
                Entity e = readObjectData(objectDef);
                game.addEntity(e);
            }
        }

        return true;
    }

    return false;
}

/** Pre-computed Matrices for shader. */
struct matrix_data_t {
    Mat4f model;
    Mat4f view;
    Mat4f mvp;
};

/** Light data for shader. */
struct light_data_t {
    int offsets[4]{0, 0, 0, 0};
    GLSLLight lights[16];
};

static matrix_data_t matrixData; /**< matrix data */
static light_data_t lightData;   /**< light data */

bool Game::init () {
    if (!readSceneData(*this, "./data/scene.json")) {
        gConsole.errorf("Failed to create scene.\n");
        return false;
    }

    for (auto &shader : mShaders) {
        shader.second.compile();

        if (!shader.second.isCompiled()) {
            gConsole.errorf("Error compiling shader -- %s.\n",
                           shader.first.c_str());
            return false;
        }
    }

    for (auto &e : mObjects) {
        e.mr.compile();
        if (!e.mr.isCompiled()) {
            gConsole.errorf("Error compiling mesh.\n");
            return false;
        }
    }

    // Emulate a camera/view transform
    view = Transform();
    view.position = Vec3f(0.0f, 3.0f, 18.0f);

    lightData.lights[0] = GLSLLight(Vec3f(0.05f, 0.001f, 0.01f),  Vec3f(0.0f, 4.0f, 0.0f),   Vec3f(0.0f, -1.0f, 0.0f), GLSLAttenuation(1.0f, 0.5f, 0.2f), 0.0f);
    lightData.lights[1] = GLSLLight(Vec3f(1.0f, 1.0f, 0.5f),     Vec3f(0.0f, 4.0f, 0.0f),   Vec3f(1.0f, -1.0f, 0.0f).normalize(), GLSLAttenuation(1.0f, 0.5f, 0.2f), 0.0f);
    lightData.lights[2] = GLSLLight(Vec3f(0.02f, 0.02f, 0.08f),     Vec3f(0.0f, -4.0f, 0.0f),   Vec3f(0.0f, 1.0f, 0.0f), GLSLAttenuation(1.0f, 0.5f, 0.2f), 0.0f);
    lightData.lights[3] = GLSLLight(Vec3f(2.0f, 2.0f, 0.0f),     Vec3f(-3.0f, 7.0f, -5.0f),   Vec3f(0.0f, 0.0f, 0.0f), GLSLAttenuation(1.0f, 1.0f, 1.0f), 5.0f);
    lightData.lights[4] = GLSLLight(Vec3f(0.2f, 0.2f, 3.0f),     Vec3f(-10.0f, 4.0f, 0.0f),   Vec3f(0.0f, 0.0f, 0.0f), GLSLAttenuation(1.0f, 1.0f, 1.0f), 20.0f);
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

void Game::input () {

    if (Input::keyDown(']')) {
        proj.fov += 1.0f;
    }
    if (Input::keyDown('[')) {
        proj.fov -= 1.0f;
    }

    if (Input::keyReleased('r')) {
        imageManager.reload();
        for (auto &shader : mShaders) {
            shader.second.compile();
        }
    }

    if (Input::keyDown('a')) {
        view.position += view.right() * -camSpeed;
    }
    if (Input::keyDown('d')) {
        view.position += view.right() * camSpeed;
    }
    if (Input::keyDown('w')) {
        view.position += view.forward() * -camSpeed;
    }
    if (Input::keyDown('s')) {
        view.position += view.forward() * camSpeed;
    }

    if (Input::mbPressed(1)) {
        Input::lockMouse();
    }

    if (Input::mbReleased(1)) {
        Input::releaseMouse();
    }

    float sensitivity = 0.01f;
    if (Input::isMouseLocked()) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        Vec2f deltaPos = Input::mouseDelta();

        bool rotX = deltaPos.y != 0;
        bool rotY = deltaPos.x != 0;

        if (rotX) {
            view.rotateL(-deltaPos.y * sensitivity, Vec3f_X);
        }

        if (rotY) {
            view.rotateW(-deltaPos.x * sensitivity, Vec3f_Y);
        }
    }
}

void Game::update (const double deltaSeconds) {
    static double t;
    Entity *obj = &mObjects[1];
    obj->transform.rotateL(math::rad(18.0f) * deltaSeconds, Vec3f_Y); // One rotation in 20 seconds

    t += deltaSeconds;
    lightData.lights[3].position.y = sinf(t) * 5.0f + 5.0f;
    lightData.lights[4].position.x = cosf(t / 10.0f) * 32.0f;
    lightData.lights[4].position.z = sinf(t) * 5.0f + 5.0f;
}

void Game::render () {
    Mat4f viewMat = proj.perspectiveProjection(mWidth, mHeight) *
        view.viewTransformationMatrix();

    glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
    GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    memcpy(p, &lightData, sizeof(light_data_t));
    glUnmapBuffer(GL_UNIFORM_BUFFER);

    // Custom drawing...
    GLSLProgram *shader;
    for (const auto &e : mObjects) {
        shader = bindShader(e.shader);

        // TODO [smh] Uniform buffer for transformations.
        // TODO [smh] Begin Frame...
        // Setup Matrix data for Draw.
        matrixData.model = e.transform.transformationMatrix();
        matrixData.view = view.viewTransformationMatrix();
        matrixData.mvp = viewMat * e.transform.transformationMatrix();

        glBindBuffer(GL_UNIFORM_BUFFER, matBuffer);
        p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
        memcpy(p, &matrixData, sizeof(matrix_data_t));
        glUnmapBuffer(GL_UNIFORM_BUFFER);

        shader->setUniform("eyePos", view.position);

        shader->bindUniformBuffer("MatrixBlock", matBuffer, 1);
        shader->bindUniformBuffer("LightingBlock", lightBuffer, 2);

        // TODO [smh] Uniform buffer for current material.
        shader->setUniform("material.specIntensity", e.mat.specIntensity);
        shader->setUniform("material.specExponent", e.mat.specExponent);

        Image *i = imageManager.get(e.texture);
        i->bind();

        e.mr.render();
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Show World Axis
    debugGfx.edge(Vec3f_Zero, Vec3f(0.0f, 1000.0f, 0.0f),
                Color::fromHex("#0000FF"));
    debugGfx.edge(Vec3f_Zero, Vec3f(1000.0f, 0.0f, 0.0f),
                Color::fromHex("#FF0000"));
    debugGfx.edge(Vec3f_Zero, Vec3f(0.0f, 0.0f, 1000.0f),
                Color::fromHex("#00FF00"));

    // test Point Light positions
    debugGfx.point(lightData.lights[3].position, 0.1f, Color(255, 255, 0));
    debugGfx.point(lightData.lights[4].position, 0.1f, Color(0, 0, 255));

    shader = bindShader("debug");
    shader->setUniform("mvp", viewMat);
    debugGfx.render();

    debugGfx.clear();
}

GLSLProgram * Game::bindShader (const std::string &pKey) {
    auto shader = &(mShaders[pKey]);

    shader->bind();
    return shader;
}
