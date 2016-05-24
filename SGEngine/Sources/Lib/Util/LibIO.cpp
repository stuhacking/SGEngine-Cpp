//
// Printers for core types.
//
#include "../Lib.h"

#include <ostream>
#include <iomanip>
#include <string>

namespace sge {

// Vec2f Printer
std::ostream &operator<< (std::ostream &os, const Vec2f &vec) {
    return os << "<Vec2f " << vec.x << " " << vec.y << ">";
}

// Vec3f Printer
std::ostream &operator<< (std::ostream &os, const Vec3f &vec) {
    return os << "<Vec3f " << vec.x << " " << vec.y << " " << vec.z << ">";
}

// Vec4f Printer
std::ostream &operator<< (std::ostream &os, const Vec4f &vec) {
    return os << "<Vec4f " << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << ">";
}

// Quaternion Printer
std::ostream &operator<< (std::ostream &os, const Quaternion &quat) {
    return os << "<Quaternion (" << quat.i << " " << quat.j << " " << quat.k << ") " << quat.w << ">";
}

// Matrix2 Printer
std::ostream &operator<< (std::ostream &os, const Matrix2 &mat) {
    os << "<Matrix2 ";
    for (u8 i = 0; i < 2; ++i) {
        auto sep = "";
        os << "[";
        for (u32 j = 0; j < 2; ++j) {
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
    for (u8 i = 0; i < 4; ++i) {
        auto sep = "";
        os << "[";
        for (u32 j = 0; j < 4; ++j) {
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
    for (u8 i = 0; i < 4; ++i) {
        auto sep = "";
        os << "[";
        for (u32 j = 0; j < 4; ++j) {
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

// Transform Printer
std::ostream& operator<< (std::ostream &os, const Transform &tr) {
    Vec3f up = tr.Up();
    Vec3f f = tr.Forward();
    Vec3f r = tr.Right();
    bool uniScale = ((tr.scale.x == tr.scale.y) && (tr.scale.x == tr.scale.z));

    os << "<Transform P=" << tr.position
       << " O=[" << f.x << " " << f.y << " " << f.z
       << "|" << up.x << " " << up.y << " " << up.z
       << "|" << r.x << " " << r.y << " " << r.z
       << "] S=";

    if (uniScale) {
        os << tr.scale.x;
    } else {
        os << tr.scale;
    }
    os << ">";
    return os;
}

// Clock Printer
std::ostream& operator<< (std::ostream &os, const Clock &clock) {
    u64 ns = clock.Elapsed();
    u32 ms = ns / 1000000;
    u32 hours = ms / (1000 * 60 * 60);
    u32 mins = (ms / (1000 * 60)) % 60;
    u32 sec = (ms / 1000) % 60;
    ms = ms % 1000;

    return os << std::setfill('0') << "<Clock "
        // HH:MM:SS
              << hours << ":" << std::setw(2) << mins << ":" << std::setw(2) << sec
        // :MS
              << ":" << std::setw(3) << ms
        // Time Scale
              << " " << clock.Scale()
        // (Time Delta in seconds)
              << "x (" << clock.DeltaSeconds() << "ds) "
        // Total elapsed time in nanoseconds.
              << ns << "ns>";
}

} /* namespace sge */
