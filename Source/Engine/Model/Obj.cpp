//
// Wavefront .obj Importer
//
#include "../Engine.h"

#include <iostream>
#include <fstream>

namespace sge {

static inline
void logParseError (const std::string &file, const u32 line, const std::string &el) {
    console.Errorf("Malformed %s in %s at line: %u.\n", el.c_str(), file.c_str(), line);
}

bool ObjDocument::readFromFile (const char * const filename) {
    std::ifstream input(filename);
    if (!input) {
        console.Errorf("File not found -- %s.\n", filename);
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
            } else if ("g" == tokens[0] && !parseGroup(tokens)) {
                logParseError(filename, lineNumber, "group name");
                return false;
            } else if ("v" == tokens[0] && !parsePosition(tokens)) {
                logParseError(filename, lineNumber, "vertex position");
                return false;
            } else if ("vn" == tokens[0] && !parseNormal(tokens)) {
                logParseError(filename, lineNumber, "normal");
                return false;
            } else if ("vt" == tokens[0] && !parseTexCoord(tokens)) {
                logParseError(filename, lineNumber, "texture coordinate");
                return false;
            } else if ("f" == tokens[0] && !parseFace(tokens)) {
                logParseError(filename, lineNumber, "face");
                return false;
            }
        }

        ++lineNumber;
    }

    return true;
}

bool ObjDocument::parseName (const std::vector<std::string> &tokens) {

    if (tokens.size() >= 2) {
        name = tokens[1];
        return true;
    }

    return false;
}

bool ObjDocument::parseGroup (const std::vector<std::string> &tokens) {
    if (tokens.size() >= 2) {
        groups.push_back(ObjGroup(tokens[1]));
        return true;
    } else {
        groups.push_back(ObjGroup("name."));
        return false;
    }
}

bool ObjDocument::parsePosition (const std::vector<std::string> &tokens) {

    if (tokens.size() >= 4) {

        float x = std::stof(tokens[1]);
        float y = std::stof(tokens[2]);
        float z = std::stof(tokens[3]);

        m_positions.emplace_back(x, y, z);
        return true;
    } else {
        m_positions.emplace_back(0.0f, 0.0f, 0.0f);
        return false;
    }
}

bool ObjDocument::parseNormal (const std::vector<std::string> &tokens) {

    m_hasNormals = true;

    if (tokens.size() >= 4) {

        float x = std::stof(tokens[1]);
        float y = std::stof(tokens[2]);
        float z = std::stof(tokens[3]);

        m_normals.emplace_back(x, y, z);
        return true;
    } else {
        m_normals.emplace_back(0.0f, 0.0f, 0.0f);
        return false;
    }
}

bool ObjDocument::parseTexCoord (const std::vector<std::string> &tokens) {

    m_hasTexture = true;

    if (tokens.size() >= 3) {

        float x = std::stof(tokens[1]);
        float y = std::stof(tokens[2]);

        m_texCoords.emplace_back(x, y);
        return true;
    } else {
        m_texCoords.emplace_back(0.0f, 0.0f);
        return false;
    }
}

bool ObjDocument::parseFace (const std::vector<std::string> &tokens) {

    // Make sure we have at least one group by the time we
    // start parsing faces.
    if (groups.empty()) {
        groups.push_back(ObjGroup("default"));
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

        if (m_hasTexture) {
            curGroup->textureIndex.emplace_back(indices[0][1].empty() ? 0 : std::stoi(indices[0][1]) - 1);
            curGroup->textureIndex.emplace_back(indices[1][1].empty() ? 0 : std::stoi(indices[1][1]) - 1);
            curGroup->textureIndex.emplace_back(indices[2][1].empty() ? 0 : std::stoi(indices[2][1]) - 1);
        }

        if (m_hasNormals) {
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

    if (doc.IsValid()) {

        for (const auto &g : doc.groups) {

            for (u32 k = 2, kMax = g.VertexCount(); k < kMax; k += 3) {
                Vertex v1 = doc.Position(g.positionIndex[k - 2]);
                Vertex v2 = doc.Position(g.positionIndex[k - 1]);
                Vertex v3 = doc.Position(g.positionIndex[k]);

                if (doc.HasNormals()) {
                    v1.normal = doc.Normal(g.normalIndex[k - 2]);
                    v2.normal = doc.Normal(g.normalIndex[k - 1]);
                    v3.normal = doc.Normal(g.normalIndex[k]);
                }

                if (doc.HasTextures()) {
                    v1.texCoord = doc.TexCoord(g.textureIndex[k - 2]);
                    v2.texCoord = doc.TexCoord(g.textureIndex[k - 1]);
                    v3.texCoord = doc.TexCoord(g.textureIndex[k]);
                }

                m.AutoTriFace(v1, v2, v3);
            }
        }

    } else {
        console.Errorf("ObjDocument is invalid -- %s\n", doc.name.c_str());
    }

    return m;
}

Mesh meshFromObjDocument (const char * const filename) {
    ObjDocument doc = ObjDocument(filename);
    return meshFromObjDocument(doc);
}

} /* namespace sge */
