/*
 *
 * Created by shacking on 08/11/16.
 */
#include "../Engine.h"

#include <rapidjson/error/en.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <stdexcept>
#include <iostream>
#include <fstream>

namespace sge {

JSONFile::JSONFile (const char *const filename) {
    std::ifstream file(filename, std::ios::in | std::ios::ate);
    std::streamoff size;

    if (file.is_open()) {
        size = file.tellg();

        m_data = std::make_unique<char[]>(size + 1);
        m_data[size] = '\0';

        file.seekg(0, std::ios::beg);
        file.read(m_data.get(), size);
        file.close();

        if (doc.ParseInsitu(m_data.get()).HasParseError()) {
            console.Errorf("Error parsing %s (%d): %s\n", filename, doc.GetErrorOffset(),
                           json::GetParseError_En(doc.GetParseError()));
        }
    } else {
        console.Errorf("Error opening file: %s\n", filename);
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

Vec2f ReadVec2f (const json::Value &json) {
    if (!json.IsArray() || json.Size() < 2) {
        throw std::invalid_argument(std::string("ReadVec2f Expected list of 2 elements but got ") + FormatJSONValue(json));
    }
    auto values = json.GetArray();

    return Vec2f(values[0].GetFloat(), values[1].GetFloat());
}

Vec3f ReadVec3f (const json::Value &json) {
    if (!json.IsArray() || json.Size() < 3) {
        throw std::invalid_argument(std::string("ReadVec3f expected list of 3 elements but got ") + FormatJSONValue(json));
    }
    auto values = json.GetArray();

    return Vec3f(values[0].GetFloat(), values[1].GetFloat(), values[2].GetFloat());
}

Vec4f ReadVec4f (const json::Value &json) {
    if (!json.IsArray() || json.Size() < 4) {
        throw std::invalid_argument(std::string("ReadVec4f expected list of 4 elements but got ") + FormatJSONValue(json));
    }
    auto values = json.GetArray();

    return Vec4f(values[0].GetFloat(), values[1].GetFloat(), values[2].GetFloat(), values[3].GetFloat());
}

Quat4f ReadOrientation (const json::Value &json) {
    if (!json.IsArray() || json.Size() < 3) {
        throw std::invalid_argument(std::string("ReadOrientation expected list of 3 elements but got ") + FormatJSONValue(json));
    }
    auto values = json.GetArray();
    Quat4f quat = Quat4f::IDENTITY;

    quat *= Quat4f::AxisAngle(Vec3f::X, values[0].GetFloat());
    quat *= Quat4f::AxisAngle(Vec3f::Z, values[2].GetFloat());
    quat *= Quat4f::AxisAngle(Vec3f::Y, values[1].GetFloat());
    quat.NormalizeSelf();

    return quat;
}

Transform ReadTransform (const json::Value &json) {
    Transform t;

    if (json.HasMember("location")) {
        t.position = ReadVec3f(json["location"]);
    }

    if (json.HasMember("orientation")) {
        t.orientation = ReadOrientation(json["orientation"]);
    }

    if (json.HasMember("size")) {
        t.scale = ReadVec3f(json["size"]);
    }

    return t;
}

} /* namespace json */

} /* namespace sge */
