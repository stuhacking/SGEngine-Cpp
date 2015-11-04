/*---  SHLibIO.h - OStream formatters for SHLib types  -------------*- C++ -*---
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
#ifndef __SHLIB_SHLIBIO_H_
#define __SHLIB_SHLIBIO_H_

class ostream;

namespace sge {

std::ostream& operator<< (std::ostream &os, const Vector2 &vec);
std::ostream& operator<< (std::ostream &os, const Vector3 &vec);
std::ostream& operator<< (std::ostream &os, const Vector4 &vec);

std::ostream& operator<< (std::ostream &os, const Quaternion &quat);

std::ostream& operator<< (std::ostream &os, const Matrix2 &mat);
std::ostream& operator<< (std::ostream &os, const Matrix3 &mat);
std::ostream& operator<< (std::ostream &os, const Matrix4 &mat);

std::ostream& operator<< (std::ostream &os, const Color &col);

std::ostream& operator<< (std::ostream &os, const Vertex &vert);

} /* namespace sge */

#endif /* __SHLIB_SHLIBIO_H_ */
