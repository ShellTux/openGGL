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
