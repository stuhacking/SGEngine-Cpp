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

Vec2f readVec2f (const json::Value &json);
Vec3f readVec3f (const json::Value &json);
Vec4f readVec4f (const json::Value &json);

Transform readTransform (const json::Value &json);

} /* namespace json */

class JSONFile {
public:
    explicit JSONFile (const char *const pFilename);

    /**
     * @return Pointer to internal json document.
     */
    const json::Document *rootDocument () const { return &doc; }

private:
    std::unique_ptr<char[]> mData;
    json::Document doc;
};

} /* namespace sge */

#endif /* __SGENGINE_JSONFILE_H */
