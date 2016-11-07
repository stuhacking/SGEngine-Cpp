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
    Image texture;
    Transform transform;

    Entity(const MeshRenderer &p_mr, const Image &p_tex, const Transform &p_t)
        : mr(p_mr), texture(p_tex), transform(p_t) { }
};

class Game {
public:
    Game (const u32 width, const u32 height);

    bool Init ();

    void Input ();
    void Update (double deltaSeconds);
    void Render ();

    void AddShader (const std::string &name, const GLSLProgram &program);
    GLSLProgram * BindShader (const std::string &key);

private:
    std::vector<Entity> m_objects;
    std::unordered_map<std::string, GLSLProgram> m_shaders;

    u32 m_width;
    u32 m_height;
};

INLINE void Game::AddShader (const std::string &name, const GLSLProgram &program) {
    m_shaders.insert(std::pair<std::string, GLSLProgram>(name, program));
}
#endif /* __SDLBASIC_GAME_H */
