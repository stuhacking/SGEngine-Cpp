/*---  LibIO.h - OStream formatters for Core Lib types  -----------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Define a bunch of << overloads for SGE types.
 */
#ifndef __SGECORELIB_LIBIO_H_
#define __SGECORELIB_LIBIO_H_

class ostream;

namespace sge {

std::ostream& operator<< (std::ostream &os, const Vec2f &vec);
std::ostream& operator<< (std::ostream &os, const Vec3f &vec);
std::ostream& operator<< (std::ostream &os, const Vec4f &vec);

std::ostream& operator<< (std::ostream &os, const Quat4f &quat);

std::ostream& operator<< (std::ostream &os, const Mat2f &mat);
std::ostream& operator<< (std::ostream &os, const Mat3f &mat);
std::ostream& operator<< (std::ostream &os, const Mat4f &mat);

std::ostream& operator<< (std::ostream &os, const Color &col);

std::ostream& operator<< (std::ostream &os, const Vertex &vert);
std::ostream& operator<< (std::ostream &os, const Transform &tr);

std::ostream& operator<< (std::ostream &os, const Clock &clock);

} /* namespace sge */

#endif /* __SGECORELIB_LIBIO_H_ */
