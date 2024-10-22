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
#ifndef INCLUDE_VECTOR_CORE_HPP_
#define INCLUDE_VECTOR_CORE_HPP_

#include <GL/gl.h>
#include <cmath>

namespace openGGL {

/**
 * @class Vec3
 * @brief Represents a 3D vector for use in graphics programming.
 *
 * The Vec3 class provides basic operations for 3D vectors, including vector
 * addition, subtraction, scalar multiplication, normalization, and dot and
 * cross product calculations.
 */
class Vec3 {
public:
  GLfloat x; ///< The x component of the vector.
  GLfloat y; ///< The y component of the vector.
  GLfloat z; ///< The z component of the vector.

  /**
   * @brief Default constructor initializes the vector to (0, 0, 0).
   */
  Vec3() : x(0), y(0), z(0) {}

  /**
   * @brief Constructs a Vec3 object with the specified x, y, and z components.
   *
   * @param x The x component of the vector.
   * @param y The y component of the vector.
   * @param z The z component of the vector.
   */
  Vec3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

  /**
   * @brief Calculates the cross product of two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   * @return A Vec3 that is the cross product of a and b.
   */
  static Vec3 cross(const Vec3 &a, const Vec3 &b);

  /**
   * @brief Calculates the dot product of two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   * @return The dot product of a and b.
   */
  static GLfloat dot(const Vec3 &a, const Vec3 &b);

  /**
   * @brief Adds another vector to this vector.
   *
   * @param other The vector to add.
   * @return A new Vec3 that is the sum of this vector and other.
   */
  Vec3 operator+(const Vec3 &other) const;

  /**
   * @brief Subtracts another vector from this vector.
   *
   * @param other The vector to subtract.
   * @return A new Vec3 that is the difference of this vector and other.
   */
  Vec3 operator-(const Vec3 &other) const;

  /**
   * @brief Scales the vector by a scalar value.
   *
   * @param scalar The scalar to multiply with.
   * @return A new Vec3 that is the product of this vector and scalar.
   */
  Vec3 operator*(const GLfloat scalar) const;

  /**
   * @brief Divides the vector by a scalar value.
   *
   * @param scalar The scalar to divide by.
   * @return A new Vec3 that is the quotient of this vector and scalar.
   */
  Vec3 operator/(const GLfloat scalar) const;

  /**
   * @brief Checks if this vector is equal to another vector.
   *
   * @param other The vector to compare against.
   * @return True if the vectors are equal, false otherwise.
   */
  bool operator==(const Vec3 &other) const;

  /**
   * @brief Checks if this vector is not equal to another vector.
   *
   * @param other The vector to compare against.
   * @return True if the vectors are different, false otherwise.
   */
  bool operator!=(const Vec3 &other) const;

  /**
   * @brief Adds another vector to this vector in place.
   *
   * @param other The vector to add.
   * @return This vector added with other
   */
  Vec3 &operator+=(const Vec3 &other);

  /**
   * @brief Subtracts another vector from this vector in place.
   *
   * @param other The vector to subtract.
   * @return This vector that is the difference of this vector and other.
   */
  Vec3 &operator-=(const Vec3 &other);

  /**
   * @brief Scales the vector in place by a scalar value.
   *
   * @param scalar The scalar to multiply with.
   * @return This Vector that is the product of this vector and scalar.
   */
  Vec3 &operator*=(const GLfloat scalar);

  /**
   * @brief Divides the vector in place by a scalar value.
   *
   * @param scalar The scalar to divide by.
   * @return This Vector that is the quotient of this vector and scalar.
   */
  Vec3 &operator/=(const GLfloat scalar);

  /**
   * @brief Returns a normalized version of this vector.
   *
   * @return A new Vec3 that is this vector normalized.
   */
  Vec3 normalized() const;

  /**
   * @brief Calculates the dot product of this vector with another vector.
   *
   * @param other The vector to take the dot product with.
   * @return The dot product of this vector and other.
   */
  GLfloat dot(const Vec3 &other) const;

  /**
   * @brief Calculates the magnitude (length) of the vector.
   *
   * @return The magnitude of the vector.
   */
  GLfloat magnitude() const;

  /**
   * @brief Calculates the squared magnitude of the vector.
   *
   * @return The squared magnitude of the vector.
   */
  GLfloat magnitudeSq() const;
};

} // namespace openGGL

#endif // INCLUDE_VECTOR_CORE_HPP_
