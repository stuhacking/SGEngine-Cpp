//
// Wavefront .obj Importer
//
#include "../Engine.h"

#include <iostream>
#include <fstream>

namespace sge {

static inline
void logParseError (const std::string &file, const u32 line, const std::string &el) {
    std::cerr << "Malformed " << el << " in " << file << "on line " << line << "\n";
}

bool ObjDocument::readFromFile (const std::string &filename) {
    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Unable to find mesh file: " << filename << "\n";
        return false;
    }

    std::string line;
    u32 lineNumber = 1;

    while (std::getline(input, line)) {
        // Skip comments & blank lines
        if (line.size() > 1 && !str::StartsWith(line, "#")) {

            std::vector<std::string> tokens = str::Split(str::Trim(line));

            if (tokens[0] == "o") {
                if (!parseName(tokens)) {
                    logParseError(filename, lineNumber, "object name");
                }
            } else if (tokens[0] == "g") {
                if (!parseGroup(tokens)) {
                    logParseError(filename, lineNumber, "group name");
                }
            } else if (tokens[0] == "v") {
                if (!parsePosition(tokens)) {
                    logParseError(filename, lineNumber, "vertex position");
                }
            } else if (tokens[0] == "vn") {
                if (!parseNormal(tokens)) {
                    logParseError(filename, lineNumber, "normal");
                }
            } else if (tokens[0] == "vt") {
                if (!parseTexCoord(tokens)) {
                    logParseError(filename, lineNumber, "texture coordinate");
                }
            } else if (tokens[0] == "f") {
                if (!parseFace(tokens)) {
                    logParseError(filename, lineNumber, "face");
                }
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

    // The object group stores the indices back into the .obj data.
    ObjGroup *currentGroup = &groups.back();

    // Convert n-sided faces to tris as we go.
    for (u32 k = 3, kMax = tokens.size(); k < kMax; ++k) {
        std::vector<std::string> indices[3];
        indices[0] = str::Split(tokens[1], '/');
        indices[1] = str::Split(tokens[k - 1], '/');
        indices[2] = str::Split(tokens[k], '/');

        currentGroup->positionIndex.emplace_back(std::stoi(indices[0][0]) - 1);
        currentGroup->positionIndex.emplace_back(std::stoi(indices[1][0]) - 1);
        currentGroup->positionIndex.emplace_back(std::stoi(indices[2][0]) - 1);

        u32 idx;
        if (m_hasTexture) {
            idx = indices[0][1].empty() ? 0 : std::stoi(indices[0][1]) - 1;
            currentGroup->textureIndex.emplace_back(idx);
            idx = indices[1][1].empty() ? 0 : std::stoi(indices[1][1]) - 1;
            currentGroup->textureIndex.emplace_back(idx);
            idx = indices[2][1].empty() ? 0 : std::stoi(indices[2][1]) - 1;
            currentGroup->textureIndex.emplace_back(idx);
        }

        if (m_hasNormals) {
            idx = indices[0][2].empty() ? 0 : std::stoi(indices[0][2]) - 1;
            currentGroup->normalIndex.emplace_back(idx);
            idx = indices[1][2].empty() ? 0 : std::stoi(indices[1][2]) - 1;
            currentGroup->normalIndex.emplace_back(idx);
            idx = indices[2][2].empty() ? 0 : std::stoi(indices[2][2]) - 1;
            currentGroup->normalIndex.emplace_back(idx);
        }
    }

    return true;
}

// --------------------------------------------------------------------------

Mesh meshFromObjDocument (const ObjDocument &doc) {
    Mesh m;

    if (doc.IsValid()) {

        for (const auto &g : doc.groups) {

            for (u32 k = 2, kMax = g.Size(); k < kMax; k += 3) {
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
        std::cerr << "ObjDocument appears to be invalid: " << doc.name << "\n";
    }

    return m;
}

Mesh meshFromObjDocument (const std::string &filename) {
    ObjDocument doc = ObjDocument(filename);
    return meshFromObjDocument(doc);
}

} /* namespace sge */
