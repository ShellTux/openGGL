#include "openGGL/3D/geometric-figures-unit.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int width = 600;
const int height = 600;
const char *windowClass = "OpenGL";
const char *title = "OpenGL 3D Geometry";
GLfloat angleX = 0.f;
GLfloat angleY = 0.f;
GLfloat angleZ = 0.f;

constexpr int quadRows = 5;
constexpr int quadCols = 5;

unsigned char colors[quadRows][quadCols][4];

void framebuffer_callback(GLFWwindow *window, int width, int height) {
  (void)window;
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, -1, 1);
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
  case GLFW_KEY_5:
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
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

void update() {
  angleX += 1.5f;
  angleY += 1.9f;
  angleZ += 0.7f;
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glColor3f(1, 1, 1);

  glPushMatrix();
  {
    glScalef(.5, .5, .5);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);
    openGGL::GeometricFigures3D::Unit::Cube();
  }
  glPopMatrix();
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

  GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_callback);
  glfwSetKeyCallback(window, key_callback);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

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
