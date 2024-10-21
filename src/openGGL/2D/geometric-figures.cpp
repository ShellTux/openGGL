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
#include "openGGL/2D/geometric-figures.hpp"
#include "openGGL/constants.hpp"

#include <GL/gl.h>
#include <cmath>
#include <cstdint>

namespace openGGL::GeometricFigures2D {

void Rect(const GLfloat xPos, const GLfloat yPos, const GLfloat width,
          const GLfloat height) {
  glBegin(GL_QUADS);

  glVertex2f(xPos, yPos);
  glVertex2f(xPos, yPos + height);
  glVertex2f(xPos + width, yPos + height);
  glVertex2f(xPos + width, yPos);

  glEnd();
}

void Circle(const GLfloat xPos, const GLfloat yPos, const GLfloat radius,
            const int resolution) {
  const GLfloat deltaAngle = 2.f * PI / resolution;

  glBegin(GL_POLYGON);

  for (GLfloat angle = 0; angle < 2 * PI; angle += deltaAngle) {
    using std::cos, std::sin;

    glVertex2f(xPos + radius * cos(angle), yPos + radius * sin(angle));
  }

  glEnd();
}

void Grid(const GLfloat xPos, const GLfloat yPos, const GLfloat width,
          const GLfloat height, const uint64_t rows, const uint64_t cols) {
  const GLfloat dw = width / cols;
  const GLfloat dh = height / rows;

  // FIX: Grid not working
  glBegin(GL_QUADS);
  for (uint64_t i = 0; i < rows; ++i) {
    for (uint64_t j = 0; j < cols; ++j) {
      glVertex2f(xPos + j * dw, yPos + i * dh);
      glVertex2f(xPos + j * dw, yPos + (i + 1) * dh);
      glVertex2f(xPos + (j + 1) * dw, yPos + (i + 1) * dh);
      glVertex2f(xPos + (j + 1) * dw, yPos + i * dh);
    }
  }
  glEnd();
}

void Point(const GLfloat xPos, const GLfloat yPos) {
  glBegin(GL_POINTS);
  glVertex2d(xPos, yPos);
  glEnd();
}

} // namespace openGGL::GeometricFigures2D
