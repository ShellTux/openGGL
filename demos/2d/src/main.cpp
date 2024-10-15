#include "openGGL/2D/geometric-figures-unit.hpp"
#include "openGGL/2D/geometric-figures.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int width = 600;
const int height = 600;
const char *windowClass = "OpenGL";
GLfloat angle = 0.f;

constexpr int quadRows = 5;
constexpr int quadCols = 5;

constexpr GLfloat quadWidth = 1.f * width / quadRows;
constexpr GLfloat quadHeight = 1.f * height / quadCols;

unsigned char colors[quadRows][quadCols][4];

void framebuffer_callback(GLFWwindow *window, int width, int height) {
  (void)window;
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void inline key_press(GLFWwindow *window, int key, int scancode, int mods) {
  (void)window;
  (void)scancode;
  (void)mods;

  switch (key) {
  case GLFW_KEY_1:
    glDisable(GL_CULL_FACE);
    break;
  case GLFW_KEY_2:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    break;
  case GLFW_KEY_3:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    break;
  case GLFW_KEY_4:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT_AND_BACK);
    break;
  }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  (void)mods;
  switch (action) {
  case GLFW_PRESS: {
    key_press(window, key, scancode, action);
  } break;
  }
}

void error_callback(int error, const char *description) {
  (void)error;
  std::cerr << "Error: " << description << std::endl;
}

void update() { angle += 1.5f; }

constexpr int attribStackMask =
    GL_COLOR_BUFFER_BIT | GL_LINE_BIT | GL_POINT_BIT;

#define QUAD_UNIT(ROW, COL, WIDTH, HEIGHT, CODE)                               \
  {                                                                            \
    glPushMatrix();                                                            \
    {                                                                          \
      constexpr int quadN = (COL);                                             \
      constexpr int quadM = (ROW);                                             \
      constexpr GLfloat x = quadWidth * (quadN + .5);                          \
      constexpr GLfloat y = quadHeight * (quadM + .5);                         \
                                                                               \
      glTranslatef(x, y, 0);                                                   \
      glScalef(quadWidth, quadHeight, 1);                                      \
      glRotatef(angle, 0, 0, 1);                                               \
                                                                               \
      glPushAttrib(attribStackMask);                                           \
      glColor3ubv(colors[quadN][quadM]);                                       \
      CODE;                                                                    \
      glPopAttrib();                                                           \
    }                                                                          \
    glPopMatrix();                                                             \
  }

#define QUAD(ROW, COL, WIDTH, HEIGHT, CODE)                                    \
  {                                                                            \
    glPushMatrix();                                                            \
    {                                                                          \
      constexpr int quadN = (COL);                                             \
      constexpr int quadM = (ROW);                                             \
      constexpr GLfloat x = quadWidth * quadN;                                 \
      constexpr GLfloat y = quadHeight * quadM;                                \
                                                                               \
      glPushAttrib(attribStackMask);                                           \
      glColor3ubv(colors[quadN][quadM]);                                       \
      CODE;                                                                    \
      glPopAttrib();                                                           \
    }                                                                          \
    glPopMatrix();                                                             \
  }

void draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();

  QUAD_UNIT(1, 0, quadWidth, quadHeight,
            { openGGL::GeometricFigures2D::Unit::Square(); })

  QUAD_UNIT(1, 1, quadWidth, quadHeight,
            { openGGL::GeometricFigures2D::Unit::Circle(); })

  QUAD_UNIT(1, 2, quadWidth, quadHeight,
            { openGGL::GeometricFigures2D::Unit::Grid(3, 3); })

  QUAD_UNIT(1, 3, quadWidth, quadHeight, {
    glPointSize(10);
    openGGL::GeometricFigures2D::Unit::Point();
  })

  QUAD_UNIT(1, 4, quadWidth, quadHeight, {
    glPointSize(10);
    openGGL::GeometricFigures2D::Unit::Triangle();
  })

  QUAD(3, 0, quadWidth, quadHeight,
       { openGGL::GeometricFigures2D::Rect(x, y, quadWidth, quadHeight); })

  QUAD(3, 1, quadWidth, quadHeight, {
    openGGL::GeometricFigures2D::Circle(x + quadWidth * .5, y + quadHeight * .5,
                                        quadWidth * .5);
  })

  QUAD(3, 2, quadWidth, quadHeight, {
    openGGL::GeometricFigures2D::Grid(x, y, quadWidth, quadHeight, 3, 3);
  })

  QUAD(3, 3, quadWidth, quadHeight, {
    glPointSize(10);
    openGGL::GeometricFigures2D::Point(x + quadWidth * .5, y + quadHeight * .5);
  })
}

int main() {
  std::srand(static_cast<unsigned int>(time(0)));

  for (int i = 0; i < quadRows; ++i) {
    for (int j = 0; j < quadCols; ++j) {
      for (int k = 0; k < 3; ++k) {
        using std::abs;

        unsigned char *color = &colors[i][j][k];
        *color = static_cast<unsigned char>(rand()) % 256;
      }

      colors[i][j][3] = 255;
    }
  }

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    return -1;
  }

  glfwWindowHintString(GLFW_X11_CLASS_NAME, windowClass);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, windowClass);

  GLFWwindow *window =
      glfwCreateWindow(width, height, "OpenGL 2D Geometry", nullptr, nullptr);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_callback);
  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window)) {
    update();
    draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
