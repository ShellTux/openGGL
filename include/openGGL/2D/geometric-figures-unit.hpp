#ifndef INCLUDE_2D_GEOMETRIC_FIGURES_UNIT_HPP_
#define INCLUDE_2D_GEOMETRIC_FIGURES_UNIT_HPP_

#include <GL/gl.h>
#include <cstdint>

namespace openGGL::GeometricFigures2D::Unit {

void Circle(const int resolution = 360);
void Grid(const uint64_t rows, const uint64_t cols);
void Point();
void Square();
void Triangle();

} // namespace openGGL::GeometricFigures2D::Unit

#endif // INCLUDE_2D_GEOMETRIC_FIGURES_UNIT_HPP_
