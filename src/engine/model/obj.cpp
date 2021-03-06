//
// Wavefront .obj Importer
//
#include "../engine.h"

#include <iostream>
#include <fstream>

namespace sge {

static inline
void logParseError (const std::string &file, const u32 line, const std::string &el) {
    gConsole.errorf("Malformed %s in %s at line: %u.\n",
                    el.c_str(),
                    file.c_str(), line);
}

bool ObjDocument::readFromFile (const char * const filename) {
    std::ifstream input(filename);
    if (!input) {
        gConsole.errorf("File not found -- %s.\n", filename);
        return false;
    }

    std::string line;
    u32 lineNumber = 1;

    while (std::getline(input, line)) {
        // Skip comments & blank lines
        if (line.size() > 1 && !str::startsWith(line, "#")) {

            std::vector<std::string> tokens = str::split(str::trim(line));

            if ("o" == tokens[0] && !parseName(tokens)) {
                logParseError(filename, lineNumber, "object name");
                return false;
            }

            if ("g" == tokens[0] && !parseGroup(tokens)) {
                logParseError(filename, lineNumber, "group name");
                return false;
            }

            if ("v" == tokens[0] && !parsePosition(tokens)) {
                logParseError(filename, lineNumber, "vertex position");
                return false;
            }

            if ("vn" == tokens[0] && !parseNormal(tokens)) {
                logParseError(filename, lineNumber, "normal");
                return false;
            }

            if ("vt" == tokens[0] && !parseTexCoord(tokens)) {
                logParseError(filename, lineNumber, "texture coordinate");
                return false;
            }

            if ("f" == tokens[0] && !parseFace(tokens)) {
                logParseError(filename, lineNumber, "face");
                return false;
            }
        }

        ++lineNumber;
    }

    return true;
}

bool ObjDocument::parseName (const std::vector<std::string> &tokens) {

    if (tokens.size() > 1) {
        name = tokens[1];
        return true;
    }

    return false;
}

bool ObjDocument::parseGroup (const std::vector<std::string> &tokens) {
    if (tokens.size() >= 2) {
        groups.emplace_back(ObjGroup(tokens[1]));
        return true;
    } else {
        groups.emplace_back(ObjGroup("name."));
        return false;
    }
}

bool ObjDocument::parsePosition (const std::vector<std::string> &tokens) {

    if (tokens.size() >= 4) {

        float x = std::stof(tokens[1]);
        float y = std::stof(tokens[2]);
        float z = std::stof(tokens[3]);

        mPositions.emplace_back(x, y, z);
        return true;
    } else {
        mPositions.emplace_back(0.0f, 0.0f, 0.0f);
        return false;
    }
}

bool ObjDocument::parseNormal (const std::vector<std::string> &tokens) {

    mHasNormals = true;

    if (tokens.size() >= 4) {

        float x = std::stof(tokens[1]);
        float y = std::stof(tokens[2]);
        float z = std::stof(tokens[3]);

        mNormals.emplace_back(x, y, z);
        return true;
    } else {
        mNormals.emplace_back(0.0f, 0.0f, 0.0f);
        return false;
    }
}

bool ObjDocument::parseTexCoord (const std::vector<std::string> &tokens) {

    mHasTexture = true;

    if (tokens.size() >= 3) {

        float x = std::stof(tokens[1]);
        float y = std::stof(tokens[2]);

        mTexCoords.emplace_back(x, y);
        return true;
    } else {
        mTexCoords.emplace_back(0.0f, 0.0f);
        return false;
    }
}

bool ObjDocument::parseFace (const std::vector<std::string> &tokens) {

    // Make sure we have at least one group by the time we
    // start parsing faces.
    if (groups.empty()) {
        groups.emplace_back(ObjGroup("default"));
    }

    if (tokens.size() < 4) {
        return false;
    }

    // Add new faces to the most recent group.
    ObjGroup *curGroup = &groups.back();

    // Convert n-sided faces to tris as we go.
    for (std::vector<std::string>::size_type k = 3, kMax = tokens.size(); k < kMax; ++k) {
        std::vector<std::string> indices[3];
        indices[0] = str::split(tokens[1], '/');
        indices[1] = str::split(tokens[k - 1], '/');
        indices[2] = str::split(tokens[k], '/');

        curGroup->positionIndex.emplace_back(std::stoi(indices[0][0]) - 1);
        curGroup->positionIndex.emplace_back(std::stoi(indices[1][0]) - 1);
        curGroup->positionIndex.emplace_back(std::stoi(indices[2][0]) - 1);

        if (mHasTexture) {
            curGroup->textureIndex.emplace_back(indices[0][1].empty() ? 0 : std::stoi(indices[0][1]) - 1);
            curGroup->textureIndex.emplace_back(indices[1][1].empty() ? 0 : std::stoi(indices[1][1]) - 1);
            curGroup->textureIndex.emplace_back(indices[2][1].empty() ? 0 : std::stoi(indices[2][1]) - 1);
        }

        if (mHasNormals) {
            curGroup->normalIndex.emplace_back(indices[0][2].empty() ? 0 : std::stoi(indices[0][2]) - 1);
            curGroup->normalIndex.emplace_back(indices[1][2].empty() ? 0 : std::stoi(indices[1][2]) - 1);
            curGroup->normalIndex.emplace_back(indices[2][2].empty() ? 0 : std::stoi(indices[2][2]) - 1);
        }
    }

    return true;
}

// --------------------------------------------------------------------------

Mesh meshFromObjDocument (const ObjDocument &doc) {
    Mesh m;

    if (doc.isValid()) {

        for (const auto &g : doc.groups) {

            for (size_t k = 2, kMax = g.vertexCount(); k < kMax; k += 3) {
                Vec3f p1, p2, p3;
                Vec3f n1, n2, n3;
                Vec2f t1, t2, t3;

                p1 = doc.position(g.positionIndex[k - 2]);
                p2 = doc.position(g.positionIndex[k - 1]);
                p3 = doc.position(g.positionIndex[k]);

                if (doc.hasNormals()) {
                    n1 = doc.normal(g.normalIndex[k - 2]);
                    n2 = doc.normal(g.normalIndex[k - 1]);
                    n3 = doc.normal(g.normalIndex[k]);
                }

                if (doc.hasTexture()) {
                    t1 = doc.texCoord(g.textureIndex[k - 2]);
                    t2 = doc.texCoord(g.textureIndex[k - 1]);
                    t3 = doc.texCoord(g.textureIndex[k]);
                }

                const Color col = Color(255, 255, 255, 255);
                m.autoFace(Vertex(p1, n1, t1, col),
                           Vertex(p2, n2, t2, col),
                           Vertex(p3, n3, t3, col));
            }
        }

    } else {
        gConsole.errorf("ObjDocument is invalid -- %s\n", doc.name.c_str());
    }

    return m;
}

Mesh meshFromObjDocument (const char * const filename) {
    ObjDocument doc = ObjDocument(filename);
    return meshFromObjDocument(doc);
}

} /* namespace sge */
