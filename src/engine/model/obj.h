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
    size_t vertexCount () const { return positionIndex.size(); }

    /** @return The number of faces in the group. */
    size_t faceCount () const { return positionIndex.size() / 3; }
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
    bool hasNormals () const { return mHasNormals; }

    /** @return True is this .obj document uses textures. */
    bool hasTexture () const { return mHasTexture; }

    /** @return The number of vertices in this .obj document. */
    size_t vertexCount () const;

    /**
     * Count the faces in this .obj document as the sum of the facecounts of
     * each object group.
     *
     * @return The number of faces in this .obj document.
     */
    size_t faceCount () const;

    /** @return True is this .obj document was parsed successfully. */
    bool isValid () const { return mIsValid; }

    Vec3f position (const s32 index) const { return mPositions[index]; }
    Vec3f normal (const s32 index) const { return mNormals[index]; }
    Vec2f texCoord (const s32 index) const { return mTexCoords[index]; }

private:
    std::vector<Vec3f> mPositions;
    std::vector<Vec3f> mNormals;
    std::vector<Vec2f> mTexCoords;

    bool mHasNormals;
    bool mHasTexture;
    bool mIsValid;

    bool readFromFile (const char * const filename);
    bool parseName (const std::vector<std::string> &tokens);
    bool parseGroup (const std::vector<std::string> &tokens);
    bool parsePosition (const std::vector<std::string> &tokens);
    bool parseNormal (const std::vector<std::string> &tokens);
    bool parseTexCoord (const std::vector<std::string> &tokens);
    bool parseFace (const std::vector<std::string> &tokens);
};

// --------------------------------------------------------------------------

inline ObjDocument::ObjDocument (const char * const filename) {
    name = "untitled_obj";

    groups.reserve(DEFAULT_GROUP_SIZE);
    mPositions.reserve(DEFAULT_MESH_SIZE);
    mNormals.reserve(DEFAULT_MESH_SIZE);
    mTexCoords.reserve(DEFAULT_MESH_SIZE);

    mHasNormals = false;
    mHasTexture = false;
    mIsValid = false;

    mIsValid = readFromFile(filename);
}

inline size_t ObjDocument::vertexCount () const {
    return mPositions.size();
}

inline size_t ObjDocument::faceCount () const {
    size_t result = 0;

    for (const auto &group : groups) {
        result += group.faceCount();
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
