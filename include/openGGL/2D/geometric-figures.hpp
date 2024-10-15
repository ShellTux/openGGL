#ifndef INCLUDE_2D_GEOMETRIC_FIGURES_H_
#define INCLUDE_2D_GEOMETRIC_FIGURES_H_

#include <GL/gl.h>
#include <cstdint>

namespace openGGL::GeometricFigures {

void Rect(const GLfloat xPos, const GLfloat yPos, const GLfloat width,
          const GLfloat height);
void Circle(const GLfloat xPos, const GLfloat yPos, const GLfloat radius,
            const int resolution = 360);
void Grid(const GLfloat xPos, const GLfloat yPos, const GLfloat width,
          const GLfloat height, const uint64_t rows, const uint64_t cols);
void Point(const GLfloat xPos, const GLfloat yPos);

} // namespace openGGL::GeometricFigures

#endif // INCLUDE_2D_GEOMETRIC_FIGURES_H_
