/*---  Game.h - Sample Demo game using SGE  ------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * (Also some feature incubation...)
 */
#ifndef __SGEDEMO_GAME_H
#define __SGEDEMO_GAME_H

#include <vector>
#include <map>
#include <string>

#include "engine.h"

using namespace sge;

struct Material {
    float specIntensity;
    float specExponent;
};

class Entity {
public:
    Transform transform;
    MeshRenderer mr;
    Material mat;
    std::string texture;
    std::string shader;

    Entity (const Transform &pTransform,
            const MeshRenderer &pMeshRenderer,
            const Material &pMat,
            const std::string &pTex,
            const std::string &pShader)
            : transform{pTransform}, mr{pMeshRenderer}, mat{pMat},
              texture{pTex}, shader{pShader} { }
};

class Game {
public:
    explicit Game (const u32 width, const u32 height)
            : mWidth{width}, mHeight{height} { }

    bool init ();

    void input ();
    void update (double deltaSeconds);
    void render ();

    void addShader (const std::string &pName, const GLSLProgram &pShader);
    GLSLProgram* bindShader (const std::string &pKey);

    void addEntity (const Entity &e);

private:
    std::vector<Entity> mObjects;
    std::map<std::string, GLSLProgram> mShaders;

    u32 mWidth;
    u32 mHeight;
};

inline void Game::addShader (const std::string &pName,
                             const GLSLProgram &pShader) {
    mShaders.insert(std::pair<std::string, GLSLProgram>(pName, pShader));
}

inline void Game::addEntity (const Entity &e) {
    mObjects.push_back(e);
}

#endif /* __SGEDEMO_GAME_H */
