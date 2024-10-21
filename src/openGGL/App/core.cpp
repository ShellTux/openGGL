#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <openGGL/App/core.hpp>
#include <string>
#include <unordered_map>
#include <utility>

namespace FramebufferSizeCallback {

static void Unit2D(GLFWwindow *window, int width, int height) {
  (void)window;
  glViewport(0, 0, width, height);
}

static void Unit3D(GLFWwindow *window, int width, int height) {
  (void)window;
  (void)width;
  (void)height;
}

static void Screen2D(GLFWwindow *window, int width, int height) {
  (void)window;
  glViewport(0, 0, width, height);

  // Update projection here for rendering consistency after resize
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void Screen3D(GLFWwindow *window, int width, int height) {
  (void)window;
  (void)width;
  (void)height;
}

} // namespace FramebufferSizeCallback

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

App &App::setFramebufferSizeCallback(const DisplayMode mode) {
  using callback = void (*)(GLFWwindow *, int, int);

  static const std::unordered_map<DisplayMode, callback> displayModeMap = {
      {DisplayMode::Unit2D, FramebufferSizeCallback::Unit2D},
      {DisplayMode::Unit3D, FramebufferSizeCallback::Unit3D},
      {DisplayMode::Screen2D, FramebufferSizeCallback::Screen2D},
      {DisplayMode::Screen3D, FramebufferSizeCallback::Screen3D},
  };

  glfwSetFramebufferSizeCallback(window, displayModeMap.at(mode));

  return *this;
}

App::App(const int width, const int height) : App(width, height, "") {}
App::App(const int width, const int height, const std::string &title) {
  if (glfwInit() == 0) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHintString(GLFW_X11_CLASS_NAME, windowClass);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, windowClass);

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback::Unit2D);

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

} // namespace openGGL
