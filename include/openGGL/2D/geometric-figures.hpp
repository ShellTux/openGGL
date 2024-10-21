#ifndef INCLUDE_2D_GEOMETRIC_FIGURES_H_
#define INCLUDE_2D_GEOMETRIC_FIGURES_H_

#include <GL/gl.h>
#include <cstdint>

namespace openGGL::GeometricFigures2D {

/**
 * Draws a rectangle at the specified position with a given width and height.
 *
 * @param xPos    The x position of the rectangle.
 * @param yPos    The y position of the rectangle.
 * @param width    The width of the rectangle.
 * @param height   The height of the rectangle.
 */
void Rect(const GLfloat xPos, const GLfloat yPos, const GLfloat width,
          const GLfloat height);

/**
 * Draws a circle at the specified position with a given radius.
 *
 * @param xPos     The x position of the circle.
 * @param yPos     The y position of the circle.
 * @param radius    The radius of the circle.
 * @param resolution The number of segments used to create the circle. Default
 * is 360.
 */
void Circle(const GLfloat xPos, const GLfloat yPos, const GLfloat radius,
            const int resolution = 360);

/**
 * Draws a grid starting at a specific position with defined dimensions.
 *
 * @param xPos      The x position of the grid.
 * @param yPos      The y position of the grid.
 * @param width      The width of the grid.
 * @param height     The height of the grid.
 * @param rows       The number of rows in the grid.
 * @param cols       The number of columns in the grid.
 */
void Grid(const GLfloat xPos, const GLfloat yPos, const GLfloat width,
          const GLfloat height, const uint64_t rows, const uint64_t cols);

/**
 * Draws a point at the specified position.
 *
 * @param xPos    The x position of the point.
 * @param yPos    The y position of the point.
 */
void Point(const GLfloat xPos, const GLfloat yPos);

} // namespace openGGL::GeometricFigures2D

#endif // INCLUDE_2D_GEOMETRIC_FIGURES_H_
