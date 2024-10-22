/***************************************************************************
 * Project                                                ____  ____ _
 *                                 ___  _ __   ___ _ __  / ___|/ ___| |
 *                                / _ \| '_ \ / _ \ '_ \| |  _| |  _| |
 *                               | (_) | |_) |  __/ | | | |_| | |_| | |___
 *                                \___/| .__/ \___|_| |_|\____|\____|_____|
 *                                     |_|
 *
 * Author: Luís Góis
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the LICENSE file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include "openGGL/3D/Vector/core.hpp"

#include <GL/gl.h>
#include <cmath>
#include <stdexcept>

namespace openGGL {

Vec3 Vec3::normalized() const {
  GLfloat length = std::sqrt(x * x + y * y + z * z);
  if (length == 0) {
    throw std::runtime_error("Cannot normalize a zero vector");
  }
  return Vec3{x / length, y / length, z / length};
}

Vec3 Vec3::cross(const Vec3 &a, const Vec3 &b) {
  // TODO: Make it more readable
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

GLfloat Vec3::dot(const Vec3 &a, const Vec3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

GLfloat Vec3::dot(const Vec3 &other) const { return dot(*this, other); }

Vec3 Vec3::operator+(const Vec3 &other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3 &other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const GLfloat scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(const GLfloat scalar) const {
  if (scalar == 0) {
    throw std::runtime_error("Vec3: Division by zero error!");
  }

  return Vec3(x / scalar, y / scalar, z / scalar);
}

bool Vec3::operator==(const Vec3 &other) const {
  return x == other.x && y == other.y && z == other.z;
}

bool Vec3::operator!=(const Vec3 &other) const { return !operator==(other); }

Vec3 &Vec3::operator+=(const Vec3 &other) {
  *this = *this + other;
  return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &other) {
  *this = *this - other;
  return *this;
}

Vec3 &Vec3::operator*=(const GLfloat scalar) {
  *this = *this * scalar;
  return *this;
}

Vec3 &Vec3::operator/=(const GLfloat scalar) {
  *this = *this / scalar;
  return *this;
}

GLfloat Vec3::magnitudeSq() const { return dot(*this, *this); }
GLfloat Vec3::magnitude() const { return std::sqrt(magnitudeSq()); }

} // namespace openGGL
