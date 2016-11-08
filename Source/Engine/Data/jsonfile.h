/*---  jsonfile.h - Wrapper for JSON Document with file contents  --*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Slurps a file into memory and parses a JSON document in situ using
 *        RapidJSON.
 */
#ifndef __SGENGINE_JSONFILE_H
#define __SGENGINE_JSONFILE_H

#include <memory>
#include <rapidjson/document.h>

namespace sge {

namespace json {
using namespace rapidjson;

Vec2f ReadVec2f (const json::Value &json);
Vec3f ReadVec3f (const json::Value &json);
Vec4f ReadVec4f (const json::Value &json);

Transform ReadTransform (const json::Value &json);

} /* namespace json */

class JSONFile {
public:
    explicit JSONFile (const char *const filename);

    /**
     * @return Pointer to internal json document.
     */
    const json::Document *GetRootDocument () const;

private:
    std::unique_ptr<char[]> m_data;
    json::Document doc;
};

// --------------------------------------------------------------------------

inline const json::Document *JSONFile::GetRootDocument () const {
    return &doc;
}

} /* namespace sge */

#endif /* __SGENGINE_JSONFILE_H */
