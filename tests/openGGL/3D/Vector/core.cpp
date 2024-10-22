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
#include <gtest/gtest.h>
#include <stdexcept>

using openGGL::Vec3;

TEST(Vec3Test, Normalization) {
  Vec3 v(3.0f, 4.0f, 0.0f);
  Vec3 normalized = v.normalized();
  EXPECT_NEAR(normalized.x, 0.6f, 1e-5);
  EXPECT_NEAR(normalized.y, 0.8f, 1e-5);
  EXPECT_NEAR(normalized.z, 0.0f, 1e-5);
}

TEST(Vec3Test, NormalizationOfZeroVector) {
  Vec3 a(0.0f, 0.0f, 0.0f);
  EXPECT_THROW(a.normalized(), std::runtime_error);
}

TEST(Vec3Test, CrossProduct) {
  Vec3 a(1.0f, 2.0f, 3.0f);
  Vec3 b(4.0f, 5.0f, 6.0f);
  Vec3 crossProduct = Vec3::cross(a, b);
  EXPECT_EQ(crossProduct.x, -3.0f);
  EXPECT_EQ(crossProduct.y, 6.0f);
  EXPECT_EQ(crossProduct.z, -3.0f);
}

TEST(Vec3Test, DotProduct) {
  Vec3 a(1.0f, 2.0f, 3.0f);
  Vec3 b(4.0f, 5.0f, 6.0f);

  EXPECT_EQ(Vec3::dot(a, b), 32.0f);
  EXPECT_EQ(a.dot(b), 32.0f);
  EXPECT_EQ(b.dot(a), 32.0f);
}

TEST(Vec3Test, Addition) {
  Vec3 a(1.0f, 2.0f, 3.0f);
  Vec3 b(4.0f, 5.0f, 6.0f);
  Vec3 result = a + b;
  EXPECT_EQ(result.x, 5.0f);
  EXPECT_EQ(result.y, 7.0f);
  EXPECT_EQ(result.z, 9.0f);
}

TEST(Vec3Test, AdditionAssign) {
  Vec3 a(1.0f, 2.0f, 3.0f);
  EXPECT_EQ(a.x, 1.0f);
  EXPECT_EQ(a.y, 2.0f);
  EXPECT_EQ(a.z, 3.0f);

  a += {4.0f, 5.0f, 6.0f};
  EXPECT_EQ(a.x, 5.0f);
  EXPECT_EQ(a.y, 7.0f);
  EXPECT_EQ(a.z, 9.0f);
}

TEST(Vec3Test, Subtraction) {
  Vec3 a(4.0f, 5.0f, 6.0f);
  Vec3 b(1.0f, 2.0f, 3.0f);
  Vec3 result = a - b;
  EXPECT_EQ(result.x, 3.0f);
  EXPECT_EQ(result.y, 3.0f);
  EXPECT_EQ(result.z, 3.0f);
}

TEST(Vec3Test, SubtractionAssign) {
  Vec3 a(4.0f, 5.0f, 6.0f);
  EXPECT_EQ(a.x, 4.0f);
  EXPECT_EQ(a.y, 5.0f);
  EXPECT_EQ(a.z, 6.0f);
  a -= {1.0f, 2.0f, 3.0f};
  EXPECT_EQ(a.x, 3.0f);
  EXPECT_EQ(a.y, 3.0f);
  EXPECT_EQ(a.z, 3.0f);
}

TEST(Vec3Test, ScalarMultiplication) {
  Vec3 a(1.0f, 2.0f, 3.0f);
  Vec3 result = a * 2.0f;
  EXPECT_EQ(result.x, 2.0f);
  EXPECT_EQ(result.y, 4.0f);
  EXPECT_EQ(result.z, 6.0f);
}

TEST(Vec3Test, ScalarMultiplicationAssign) {
  Vec3 a(1.0f, 2.0f, 3.0f);
  EXPECT_EQ(a.x, 1.0f);
  EXPECT_EQ(a.y, 2.0f);
  EXPECT_EQ(a.z, 3.0f);

  a *= 2.0f;
  EXPECT_EQ(a.x, 2.0f);
  EXPECT_EQ(a.y, 4.0f);
  EXPECT_EQ(a.z, 6.0f);

  a *= 0.0f;
  EXPECT_EQ(a.x, 0);
  EXPECT_EQ(a.y, 0);
  EXPECT_EQ(a.z, 0);
}

TEST(Vec3Test, ScalarDivision) {
  Vec3 a(2.0f, 4.0f, 6.0f);
  Vec3 result = a / 2.0f;
  EXPECT_EQ(result.x, 1.0f);
  EXPECT_EQ(result.y, 2.0f);
  EXPECT_EQ(result.z, 3.0f);
}

TEST(Vec3Test, ScalarDivisionAssign) {
  Vec3 a(2.0f, 4.0f, 6.0f);
  EXPECT_EQ(a.x, 2.0f);
  EXPECT_EQ(a.y, 4.0f);
  EXPECT_EQ(a.z, 6.0f);

  a /= 2.0f;
  EXPECT_EQ(a.x, 1.0f);
  EXPECT_EQ(a.y, 2.0f);
  EXPECT_EQ(a.z, 3.0f);
}

TEST(Vec3Test, DivisionByZero) {
  Vec3 a(1.0f, 2.0f, 3.0f);
  EXPECT_THROW(a / 0.0f, std::runtime_error);
  EXPECT_THROW(a /= 0.0f, std::runtime_error);
}

TEST(Vec3Test, Equality) {
  const Vec3 a(4.0f, 5.0f, 6.0f);
  const Vec3 b(1.0f, 2.0f, 3.0f);
  const Vec3 result = a + b;
  const Vec3 expectedResult(5, 7, 9);

  EXPECT_TRUE(Vec3() == Vec3(0, 0, 0));
  EXPECT_TRUE(result == expectedResult);
  EXPECT_FALSE(result != expectedResult);
  EXPECT_TRUE(result != Vec3());
  EXPECT_FALSE(result == Vec3());
}

TEST(Vec3Test, Magnitude) {
  const Vec3 a(3, 4, -9);
  EXPECT_NEAR(a.magnitude(), 10.29563014f, 1e-5);
  EXPECT_EQ(Vec3().magnitude(), 0);
}

TEST(Vec3Test, MagnitudeSq) {
  const Vec3 a(3, 4, -9);
  EXPECT_EQ(Vec3().magnitudeSq(), 0);
  EXPECT_EQ(a.magnitudeSq(), 106);
}
