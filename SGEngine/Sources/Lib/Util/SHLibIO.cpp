#include "../Lib.h"

#include <ostream>
#include <string>

namespace sge {

// Vector2 Printer
std::ostream &operator<< (std::ostream &os, const Vector2 &vec) {
    return os << "<Vector2 " << vec.x << " " << vec.y << ">";
}

// Vector3 Printer
std::ostream &operator<< (std::ostream &os, const Vector3 &vec) {
    return os << "<Vector3 " << vec.x << " " << vec.y << " " << vec.z << ">";
}

// Vector4 Printer
std::ostream &operator<< (std::ostream &os, const Vector4 &vec) {
    return os << "<Vector4 " << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << ">";
}

// Quaternion Printer
std::ostream &operator<< (std::ostream &os, const Quaternion &quat) {
    return os << "<Quaternion (" << quat.i << " " << quat.j << " " << quat.k << ") " << quat.w << ">";
}

// Matrix2 Printer
std::ostream &operator<< (std::ostream &os, const Matrix2 &mat) {
    os << "<Matrix2 ";
    for (int i = 0; i < 2; i++) {
        auto sep = "";
        os << "[";
        for (int j = 0; j < 2; j++) {
            os << sep << mat[i][j];
            sep = " ";
        }
        os << "]";
    }
    os << ">";
    return os;
}

// Matrix3 Printer
std::ostream &operator<< (std::ostream &os, const Matrix3 &mat) {
    os << "<Matrix3 ";
    for (int i = 0; i < 4; i++) {
        auto sep = "";
        os << "[";
        for (int j = 0; j < 4; j++) {
            os << sep << mat[i][j];
            sep = " ";
        }
        os << "]";
    }
    os << ">";
    return os;
}

// Matrix4 Printer
std::ostream &operator<< (std::ostream &os, const Matrix4 &mat) {
    os << "<Matrix4 ";
    for (int i = 0; i < 4; i++) {
        auto sep = "";
        os << "[";
        for (int j = 0; j < 4; j++) {
            os << sep << mat[i][j];
            sep = " ";
        }
        os << "]";
    }
    os << ">";
    return os;
}

// Color Printer
std::ostream& operator<< (std::ostream &os, const Color &col) {
    return os << "<Color " << (unsigned)col.r << " " << (unsigned)col.g
              << " " << (unsigned)col.b << " " << (unsigned)col.a << ">";
}

// Vertex Printer
std::ostream& operator<< (std::ostream &os, const Vertex &vert) {
    return os << "<Vertex P=" << vert.position << " N=" << vert.normal
              << " T=" << vert.texCoord << " C=" << vert.color << ">";
}

} /* namespace sge */
