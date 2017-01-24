// -*- C++ -*-
#ifndef __SDLBASIC_GAME_H
#define __SDLBASIC_GAME_H

#include <vector>
#include <unordered_map>
#include <string>

#include "Engine.h"

using namespace sge;

class Entity {
public:
    MeshRenderer mr;
    std::string texture;
    Transform transform;
    std::string shader;

    Entity(const MeshRenderer &p_mr, const std::string &p_tex, const Transform &p_t, const std::string &p_shader)
        : mr(p_mr), texture(p_tex), transform(p_t), shader(p_shader) { }
};

class Game {
public:
    explicit Game (const u32 width, const u32 height)
            : m_width{width}, m_height{height} { }

    bool Init ();

    void Input ();
    void Update (double deltaSeconds);
    void Render ();

    void AddShader (const std::string &name, const GLSLProgram &program);
    GLSLProgram * BindShader (const std::string &key);

    void AddEntity (const Entity &e);
private:
    std::vector<Entity> m_objects;
    std::unordered_map<std::string, GLSLProgram> m_shaders;

    u32 m_width;
    u32 m_height;
};

inline void Game::AddShader (const std::string &name, const GLSLProgram &program) {
    m_shaders.insert(std::pair<std::string, GLSLProgram>(name, program));
}

inline void Game::AddEntity (const Entity &e) {
    m_objects.push_back(e);
}

#endif /* __SDLBASIC_GAME_H */
