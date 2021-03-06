/*
 *
 * Created by shacking on 08/11/16.
 */
#include "../engine.h"

#include <rapidjson/error/en.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <stdexcept>
#include <iostream>
#include <fstream>

namespace sge {

JSONFile::JSONFile (const char *const pFilename) {
    std::ifstream file(pFilename, std::ios::in | std::ios::ate);
    std::streamoff size;

    if (file.is_open()) {
        size = file.tellg();

        mData = std::make_unique<char[]>(size + 1);
        mData[size] = '\0';

        file.seekg(0, std::ios::beg);
        file.read(mData.get(), size);
        file.close();

        if (doc.ParseInsitu(mData.get()).HasParseError()) {
            gConsole.errorf("Error parsing %s (%d): %s\n", pFilename,
                           doc.GetErrorOffset(),
                           json::GetParseError_En(doc.GetParseError()));
        }
    } else {
        gConsole.errorf("Error opening file: %s\n", pFilename);
    }
}

namespace json {

// For error-reporting, write a json value back into a string.
static std::string FormatJSONValue (const json::Value &json) {
    json::StringBuffer buffer;
    json::Writer<StringBuffer> writer(buffer);

    json.Accept(writer);

    return buffer.GetString();
}

Vec2f readVec2f (const json::Value &json) {
    if (!json.IsArray() || json.Size() < 2) {
        throw std::invalid_argument(
                std::string("ReadVec2f Expected list of 2 elements but got ") +
                FormatJSONValue(json));
    }
    auto values = json.GetArray();

    return Vec2f(values[0].GetFloat(), values[1].GetFloat());
}

Vec3f readVec3f (const json::Value &json) {
    if (!json.IsArray() || json.Size() < 3) {
        throw std::invalid_argument(
                std::string("ReadVec3f expected list of 3 elements but got ") +
                FormatJSONValue(json));
    }
    auto values = json.GetArray();

    return Vec3f(values[0].GetFloat(), values[1].GetFloat(), values[2].GetFloat());
}

Vec4f readVec4f (const json::Value &json) {
    if (!json.IsArray() || json.Size() < 4) {
        throw std::invalid_argument(
                std::string("ReadVec4f expected list of 4 elements but got ") +
                FormatJSONValue(json));
    }
    auto values = json.GetArray();

    return Vec4f(values[0].GetFloat(), values[1].GetFloat(), values[2].GetFloat(), values[3].GetFloat());
}

Quat4f ReadOrientation (const json::Value &json) {
    if (!json.IsArray() || json.Size() < 3) {
        throw std::invalid_argument(
                std::string("ReadOrientation expected list of 3 elements but got ") +
                FormatJSONValue(json));
    }
    auto values = json.GetArray();
    Quat4f quat = Quat4f_Identity;

    quat *= Quat4f(values[0].GetFloat(), Vec3f_X);
    quat *= Quat4f(values[2].GetFloat(), Vec3f_Z);
    quat *= Quat4f(values[1].GetFloat(), Vec3f_Y);
    quat.normalizeSelf();

    return quat;
}

Transform readTransform (const json::Value &json) {
    Transform t;

    if (json.HasMember("location")) {
        t.position = readVec3f(json["location"]);
    }

    if (json.HasMember("orientation")) {
        t.orientation = ReadOrientation(json["orientation"]);
    }

    if (json.HasMember("size")) {
        t.scale = readVec3f(json["size"]);
    }

    return t;
}

} /* namespace json */

} /* namespace sge */
