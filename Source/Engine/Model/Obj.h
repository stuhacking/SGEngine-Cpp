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

/**
 * The Object document stores lists of Vec2f and Vec3f for the position,
 * normal and texture data. Faces are represented by storing indexes into
 * the global lists.
 */
class ObjGroup {
public:
    std::string name;
    std::vector<u32> positionIndex;
    std::vector<u32> normalIndex;
    std::vector<u32> textureIndex;

public:
    ObjGroup (const std::string &p_name = "") : name(p_name) { }

    /** @return The number of vertices in this group. */
    size_t VertexCount () const { return positionIndex.size(); }

    /** @return The number of faces in the group. */
    size_t FaceCount () const { return positionIndex.size() / 3; }
};

/**
 * Data from parsed .obj document.
 */
class ObjDocument {
public:
    std::string name;
    std::vector<ObjGroup> groups;

public:
    explicit ObjDocument (const char * const filename);

    /** @return True if this .obj document uses normals. */
    bool HasNormals () const { return m_hasNormals; }

    /** @return True is this .obj document uses textures. */
    bool HasTextures () const { return m_hasTexture; }

    /** @return The number of vertices in this .obj document. */
    size_t VertexCount () const;

    /**
     * Count the faces in this .obj document as the sum of the facecounts of
     * each object group.
     *
     * @return The number of faces in this .obj document.
     */
    size_t FaceCount () const;

    /** @return True is this .obj document was parsed successfully. */
    bool IsValid () const { return m_isValid; }

    Vec3f Position (const i32 index) const { return m_positions[index]; }
    Vec3f Normal (const i32 index) const { return m_normals[index]; }
    Vec2f TexCoord (const i32 index) const { return m_texCoords[index]; }

private:
    std::vector<Vec3f> m_positions;
    std::vector<Vec3f> m_normals;
    std::vector<Vec2f> m_texCoords;

    bool m_hasNormals;
    bool m_hasTexture;
    bool m_isValid;

    bool readFromFile (const char * const filename);
    bool parseName (const std::vector<std::string> &tokens);
    bool parseGroup (const std::vector<std::string> &tokens);
    bool parsePosition (const std::vector<std::string> &tokens);
    bool parseNormal (const std::vector<std::string> &tokens);
    bool parseTexCoord (const std::vector<std::string> &tokens);
    bool parseFace (const std::vector<std::string> &tokens);
};

// --------------------------------------------------------------------------

INLINE ObjDocument::ObjDocument (const char * const filename) {
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

INLINE size_t ObjDocument::VertexCount () const {
    return m_positions.size();
}

INLINE size_t ObjDocument::FaceCount () const {
    size_t result = 0;

    for (const auto &group : groups) {
        result += group.FaceCount();
    }

    return result;
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
Mesh meshFromObjDocument (const char * const filename);

} /* namespace sge */

#endif /* __SGE_OBJ_H */
