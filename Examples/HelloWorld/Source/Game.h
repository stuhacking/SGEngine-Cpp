// -*- C++ -*-
#ifndef __SDLBASIC_GAME_H
#define __SDLBASIC_GAME_H

#include <vector>

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

private:
    GLSLProgram m_objShader;
    GLSLProgram m_debugShader;

    std::vector<Entity> m_objects;

    u32 m_width;
    u32 m_height;
};

#endif /* __SDLBASIC_GAME_H */
