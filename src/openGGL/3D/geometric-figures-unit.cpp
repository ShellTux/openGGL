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
#include "openGGL/3D/geometric-figures-unit.hpp"
#include "openGGL/2D/geometric-figures-unit.hpp"
#include "openGGL/constants.hpp"

#include <GL/gl.h>

#define CUBE_MESH_IMPLEMENTATION 0
#define FACE_COLOR 0

namespace openGGL::GeometricFigures3D::Unit {

void Cube() {
  constexpr GLfloat p = .5f;

  glBegin(GL_QUADS);
#if CUBE_MESH_IMPLEMENTATION == 0
  glPushAttrib(GL_COLOR_BUFFER_BIT);

  // NOTE: Above
  glColor3ub(255, 0, 0);
  glVertex3f(-p, -p, -p);
  glVertex3f(-p, -p, p);
  glVertex3f(p, -p, p);
  glVertex3f(p, -p, -p);

  // NOTE: Below
  glColor3ub(0, 255, 0);
  glVertex3f(-p, p, -p);
  glVertex3f(p, p, -p);
  glVertex3f(p, p, p);
  glVertex3f(-p, p, p);

  // NOTE: Left
  glColor3ub(0, 0, 255);
  glVertex3f(-p, -p, -p);
  glVertex3f(-p, p, -p);
  glVertex3f(-p, p, p);
  glVertex3f(-p, -p, p);

  // NOTE: Right
  glColor3ub(255, 255, 0);
  glVertex3f(p, -p, p);
  glVertex3f(p, p, p);
  glVertex3f(p, p, -p);
  glVertex3f(p, -p, -p);

  // NOTE: Behind
  glColor3ub(255, 0, 255);
  glVertex3f(p, -p, -p);
  glVertex3f(p, p, -p);
  glVertex3f(-p, p, -p);
  glVertex3f(-p, -p, -p);

  // NOTE: Front
  glColor3ub(0, 255, 255);
  glVertex3f(-p, -p, p);
  glVertex3f(-p, p, p);
  glVertex3f(p, p, p);
  glVertex3f(p, -p, p);

  glPopMatrix();
#else
#error FIX NOT WORKING
  constexpr GLfloat angle = PI / 2;

  // NOTE: Above
  glPushMatrix();
  {
    glTranslated(0, -p, 0);
    glRotated(angle, 1, 0, 0);
    GeometricFigures2D::Unit::Square();
  }
  glPopMatrix();

  // NOTE: Below
  glPushMatrix();
  {
    glTranslated(0, p, 0);
    glRotated(-angle, 1, 0, 0);
    GeometricFigures2D::Unit::Square();
  }
  glPopMatrix();

  // NOTE: Left
  glPushMatrix();
  {
    glTranslated(-p, 0, 0);
    glRotated(angle, 1, 0, 0);
    GeometricFigures2D::Unit::Square();
  }
  glPopMatrix();

  // NOTE: Right
  glPushMatrix();
  {
    glTranslated(p, 0, 0);
    glRotated(-angle, 1, 0, 0);
    GeometricFigures2D::Unit::Square();
  }
  glPopMatrix();

  // NOTE: Behind
  glPushMatrix();
  {
    glTranslated(0, 0, -p);
    glRotated(2 * angle, 0, 1, 0);
    GeometricFigures2D::Unit::Square();
  }
  glPopMatrix();

  // NOTE: Front
  glPushMatrix();
  {
    glTranslated(0, 0, p);
    GeometricFigures2D::Unit::Square();
  }
  glPopMatrix();
#endif

  glEnd();
}

} // namespace openGGL::GeometricFigures3D::Unit
