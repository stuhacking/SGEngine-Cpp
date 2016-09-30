/*---  Obj.h - Importer for Wavefront Obj Header  ------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines functions for converting .obj documents to
 *   internal mesh format.
 */
#ifndef __SGE_OBJ_H
#define __SGE_OBJ_H

#include <string>
#include <vector>

#define DEFAULT_MESH_SIZE 128
#define DEFAULT_GROUP_SIZE 8

namespace sge {

class ObjGroup {
public:
    std::string name;
    std::vector<u32> positionIndex;
    std::vector<u32> normalIndex;
    std::vector<u32> textureIndex;

public:
    ObjGroup (const std::string &p_name = "") : name(p_name) { }

    u32 Size () const { return positionIndex.size(); }
};

/**
 * Data from parsed .obj document.
 */
class ObjDocument {
public:
    std::string name;
    std::vector<ObjGroup> groups;

public:
    ObjDocument (const std::string &filename);

    bool HasNormals () const { return m_hasNormals; }
    bool HasTextures () const { return m_hasTexture; }

    size_t Size () const { return m_positions.size(); }
    bool IsValid () const { return m_isValid; }

    Vec3f Position (const s32 index) const { return m_positions[index]; }
    Vec3f Normal (const s32 index) const { return m_normals[index]; }
    Vec2f TexCoord (const s32 index) const { return m_texCoords[index]; }

private:
    std::vector<Vec3f> m_positions;
    std::vector<Vec3f> m_normals;
    std::vector<Vec2f> m_texCoords;

    bool m_hasNormals;
    bool m_hasTexture;
    bool m_isValid;

    bool readFromFile (const std::string &filename);
    bool parseName (const std::vector<std::string> &tokens);
    bool parseGroup (const std::vector<std::string> &tokens);
    bool parsePosition (const std::vector<std::string> &tokens);
    bool parseNormal (const std::vector<std::string> &tokens);
    bool parseTexCoord (const std::vector<std::string> &tokens);
    bool parseFace (const std::vector<std::string> &tokens);
};

// --------------------------------------------------------------------------

INLINE ObjDocument::ObjDocument (const std::string &filename) {
    name = "untitled_obj";

    groups.reserve(DEFAULT_GROUP_SIZE);
    m_positions.reserve(DEFAULT_MESH_SIZE);
    m_normals.reserve(DEFAULT_MESH_SIZE);
    m_texCoords.reserve(DEFAULT_MESH_SIZE);

    m_hasNormals = false;
    m_hasTexture = false;
    m_isValid = false;

    m_isValid = readFromFile(filename);
}

// --------------------------------------------------------------------------

/**
 * Convert a parsed ObjDocument to a Mesh.
 */
Mesh meshFromObjDocument (const ObjDocument &doc);

/**
 * Convert an ObjDocument stored in a file resource
 * to a Mesh.
 */
Mesh meshFromObjDocument (const std::string &filename);

} /* namespace sge */

#endif /* __SGE_OBJ_H */
