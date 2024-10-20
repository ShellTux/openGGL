#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <openGGL/2D/geometric-figures-unit.hpp>
#include <openGGL/App/core.hpp>
#include <string>

GLfloat scale = 1.0f;
GLfloat angle = 0.0f;

#if 0
#define OPENGGL_APP_EVENTS_IMPLEMENTATION
#include <openGGL/App/events.hpp>
#else
#include <iostream>
#include <map>

namespace openGGL {

void App::keyPressed(const int key) const {
  switch (key) {
  case GLFW_KEY_0: {
    glColor3ub(255, 255, 255);
  } break;
  case GLFW_KEY_1: {
    glColor3ub(255, 0, 0);
  } break;
  case GLFW_KEY_2: {
    glColor3ub(0, 255, 0);
  } break;
  case GLFW_KEY_3: {
    glColor3ub(0, 0, 255);
  } break;
  }
}

void App::keyReleased(const int key) const {
  if (isDebugEventFlagOn(DEBUG_KEY_RELEASE)) {
    std::cout << "Released: " << glfwGetKeyName(key, 0) << std::endl;
  }
}

void App::mouseEntered() const {
  if (isDebugEventFlagOn(DEBUG_MOUSE_ENTER)) {
    std::cout << "Mouse entered Window" << std::endl;
  }
}

void App::mouseExited() const {
  if (isDebugEventFlagOn(DEBUG_MOUSE_EXIT)) {
    std::cout << "Mouse exited Window" << std::endl;
  }
}

void App::mouseMoved(const double mouseX, const double mouseY) const {
  if (isDebugEventFlagOn(DEBUG_MOUSE_MOVE)) {
    std::cout << "Mouse: (" << mouseX << ", " << mouseY << ")" << std::endl;
  }

  const auto [width, height] = getWindowSize();

  scale = mouseX / width;
}

void App::mousePressed(const int button, const int mods) const {
  (void)mods;

  using ButtonMap = std::map<int, std::string>;

  static const ButtonMap buttonNameMap = {
      {GLFW_MOUSE_BUTTON_LEFT, "Left"},
      {GLFW_MOUSE_BUTTON_RIGHT, "Right"},
      {GLFW_MOUSE_BUTTON_MIDDLE, "Middle"},
  };

  if (isDebugEventFlagOn(DEBUG_MOUSE_PRESS)) {
    std::cout << "Mouse Pressed: " << buttonNameMap.at(button) << std::endl;
  }
}

void App::mouseReleased(const int button, const int mods) const {
  (void)mods;

  static const std::map<int, std::string> buttonNameMap = {
      {GLFW_MOUSE_BUTTON_LEFT, "Left"},
      {GLFW_MOUSE_BUTTON_RIGHT, "Right"},
      {GLFW_MOUSE_BUTTON_MIDDLE, "Middle"},
  };

  if (isDebugEventFlagOn(DEBUG_MOUSE_RELEASE)) {
    std::cout << "Mouse Released: " << buttonNameMap.at(button) << std::endl;
  }
}

void App::mouseScrolled(const double xOffset, const double yOffset) const {
  if (isDebugEventFlagOn(DEBUG_MOUSE_SCROLL)) {
    std::cout << "Mouse scroll: (" << xOffset << ", " << yOffset << ")"
              << std::endl;
  }
}

} // namespace openGGL
#endif

namespace openGGL {

void App::update() { angle += 1.3f; };
void App::setup() {};

void App::draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();

  glScalef(scale, scale, 1);
  glRotatef(angle, 0, 0, 1);
  openGGL::GeometricFigures2D::Unit::Square();
};

} // namespace openGGL

int main() {
  openGGL::App app{600, 600, "app demo"};
  app.setDebugEventFlag(openGGL::App::DEBUG_KEY_PRESS)
      .setDebugEventFlag(openGGL::App::DEBUG_MOUSE_MOVE);
  app.init();

  return 0;
}
