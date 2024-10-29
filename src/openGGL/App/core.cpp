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
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <openGGL/App/core.hpp>
#include <string>
#include <utility>

static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  (void)scancode;
  (void)mods;

  using openGGL::App;

  const App *app = App::getAllApps().at(window);
  switch (action) {
  case GLFW_PRESS: {
    app->keyPressed(key);
  } break;
  case GLFW_RELEASE: {
    app->keyReleased(key);
  } break;
  }
}

static void cursorPosCallback(GLFWwindow *window, double mouseX,
                              double mouseY) {
  using openGGL::App;

  const App *app = App::getAllApps().at(window);

  app->mouseMoved(mouseX, mouseY);
}

static void cursorEnterCallback(GLFWwindow *window, int entered) {
  using openGGL::App;

  const App *app = App::getAllApps().at(window);

  if (entered != 0) {
    app->mouseEntered();
  } else {
    app->mouseExited();
  }
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                int mods) {
  using openGGL::App;

  const App *app = App::getAllApps().at(window);

  switch (action) {
  case GLFW_PRESS: {
    app->mousePressed(button, mods);
  } break;
  case GLFW_RELEASE: {
    app->mouseReleased(button, mods);
  } break;
  }
}

static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
  using openGGL::App;

  const App *app = App::getAllApps().at(window);

  app->mouseScrolled(xoffset, yoffset);
}

namespace openGGL {

App::WindowAppMap App::allApps = App::WindowAppMap();

App::WindowAppMap App::getAllApps() { return allApps; }

App &App::setDebugEventFlag(const DebugEventFlag debugEventFlag) {
  debugEventFlags |= debugEventFlag;
  return *this;
}

App &App::unsetDebugEventFlag(const DebugEventFlag debugEventFlag) {
  debugEventFlags &= ~debugEventFlag;
  return *this;
}

App &App::clearDebugEventFlags() {
  debugEventFlags = 0;
  return *this;
}

bool App::isDebugEventFlagOn(const DebugEventFlag debugEventFlag) const {
  return (debugEventFlags & debugEventFlag) != 0u;
}

App &App::setFramebufferSizeCallback(void (*callback)(GLFWwindow *, int, int)) {
  glfwSetFramebufferSizeCallback(window, callback);
  return *this;
}

App::App(const int width, const int height) : App(width, height, "") {}

App::App(const int width, const int height, const std::string &title) {
  if (glfwInit() == 0) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfwWindowHintString(GLFW_X11_CLASS_NAME, windowClass);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, windowClass);

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window,
                                 [](GLFWwindow *window, int width, int height) {
                                   (void)window;
                                   glViewport(0, 0, width, height);
                                 });

  allApps[window] = this;
}

App::~App() {
  // TODO: Remove app from allApps
  glfwTerminate();
}

std::pair<double, double> App::getMousePos() const {
  double x = -1;
  double y = -1;

  glfwGetCursorPos(window, &x, &y);

  return {x, y};
}

std::pair<int, int> App::getWindowSize() const {
  int width = -1;
  int height = -1;

  glfwGetWindowSize(window, &width, &height);

  return {width, height};
}

void App::init() {
  mSetup();
  mDraw();
}

void App::mSetup() {
  glfwSetKeyCallback(window, keyCallback);
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetCursorEnterCallback(window, cursorEnterCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetScrollCallback(window, scrollCallback);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  setup();
}

void App::mDraw() {
  std::cout << "Start drawing" << std::endl;
  while (glfwWindowShouldClose(window) == 0) {
    update();
    draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  std::cout << "End drawing" << std::endl;
}

void App::printOpenGLInfo() const {
  std::cout << "\033[32mVendor:\033[0m           " << glGetString(GL_VENDOR)
            << std::endl;
  std::cout << "\033[32mRenderer:\033[0m         " << glGetString(GL_RENDERER)
            << std::endl;
  std::cout << "\033[32mVersion:\033[0m          " << glGetString(GL_VERSION)
            << std::endl;
  std::cout << "\033[32mShading Language:\033[0m "
            << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

} // namespace openGGL
