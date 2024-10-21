#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int width = 600;
const int height = 600;
const char *windowClass = "OpenGL";

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
  (void)key;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  (void)mods;
  (void)window;
  (void)key;
  (void)scancode;
  (void)action;
}

void error_callback(int error, const char *description) {
  (void)error;
  std::cerr << "Error: " << description << std::endl;
}

void setup() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
}
void update() {}
void draw() {}

int main() {
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

  setup();

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
