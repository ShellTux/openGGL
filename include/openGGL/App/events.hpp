#ifndef INCLUDE_APP_EVENTS_CPP_
#define INCLUDE_APP_EVENTS_CPP_

#include <GLFW/glfw3.h>
#include <openGGL/App/core.hpp>

#if 0
#define OPENGGL_APP_EVENTS_IMPLEMENTATION
#endif

#ifdef OPENGGL_APP_EVENTS_IMPLEMENTATION
#include <iostream>
#include <map>
#include <string>

namespace openGGL {

void App::keyPressed(const int key) const {
  if (isDebugEventFlagOn(DEBUG_KEY_PRESS)) {
    std::cout << "Key Pressed: " << glfwGetKeyName(key, 0) << std::endl;
  }
}

void App::keyReleased(const int key) const {
  if (isDebugEventFlagOn(DEBUG_KEY_RELEASE)) {
    std::cout << "Key Released: " << glfwGetKeyName(key, 0) << std::endl;
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

#endif // OPENGGL_APP_EVENTS_IMPLEMENTATION
#endif // INCLUDE_APP_EVENTS_CPP_
