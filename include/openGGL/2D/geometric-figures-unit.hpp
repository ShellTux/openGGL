#ifndef INCLUDE_2D_GEOMETRIC_FIGURES_UNIT_HPP_
#define INCLUDE_2D_GEOMETRIC_FIGURES_UNIT_HPP_

#include <GL/gl.h>
#include <cstdint>

namespace openGGL::GeometricFigures2D::Unit {

/**
 * Draws a circle with the specified resolution.
 *
 * @param resolution The number of segments used to create the circle. Default
 * is 360.
 */
void Circle(const int resolution = 360);

/**
 * Draws a grid with the specified number of rows and columns.
 *
 * @param rows The number of rows in the grid.
 * @param cols The number of columns in the grid.
 */
void Grid(const uint64_t rows, const uint64_t cols);

/** Draws a point. */
void Point();

/** Draws a square. */
void Square();

/** Draws a triangle. */
void Triangle();

} // namespace openGGL::GeometricFigures2D::Unit

#endif // INCLUDE_2D_GEOMETRIC_FIGURES_UNIT_HPP_
