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
#include "openGGL/2D/geometric-figures-unit.hpp"
#include "openGGL/constants.hpp"

#include <GL/gl.h>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace openGGL::GeometricFigures2D::Unit {

void Circle(const int resolution) {
  constexpr GLfloat r = 0.5;
  const GLfloat deltaAngle = 2.f * PI / resolution;

  glBegin(GL_POLYGON);

  for (GLfloat angle = 0; angle < 2 * PI; angle += deltaAngle) {
    using std::cos, std::sin;

    glVertex2f(r * cos(angle), r * sin(angle));
  }

  glEnd();
}

void Square() {
  constexpr GLfloat p = 0.5;

  glBegin(GL_QUADS);

  glVertex2f(-p, -p);
  glVertex2f(-p, p);
  glVertex2f(p, p);
  glVertex2f(p, -p);

  glEnd();
}

void Grid(const uint64_t rows, const uint64_t cols) {
  constexpr GLfloat p = .5f;
  const GLfloat dw = 1.f / cols;
  const GLfloat dh = 1.f / rows;

  // FIX: Grid not working
  glBegin(GL_QUADS);
  for (uint64_t i = 0; i < rows; ++i) {
    for (uint64_t j = 0; j < cols; ++j) {
      glVertex2f(-p + j * dw, -p + i * dh);
      glVertex2f(-p + j * dw, -p + (i + 1) * dh);
      glVertex2f(-p + (j + 1) * dw, -p + (i + 1) * dh);
      glVertex2f(-p + (j + 1) * dw, -p + i * dh);
    }
  }
  glEnd();
}

void Point() {
  glBegin(GL_POINTS);
  glVertex2d(0, 0);
  glEnd();
}

void Triangle() {
  constexpr GLfloat p = .5f;
  constexpr GLfloat p2 = 0.3535533906;

  glBegin(GL_POLYGON);
  {
    glVertex2d(0, -p);
    glVertex2d(-p2, p2);
    glVertex2d(p2, p2);
  }
  glEnd();
}

} // namespace openGGL::GeometricFigures2D::Unit
