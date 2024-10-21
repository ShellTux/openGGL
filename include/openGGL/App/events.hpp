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
#ifndef INCLUDE_APP_EVENTS_CPP_
#define INCLUDE_APP_EVENTS_CPP_

#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <openGGL/App/core.hpp>
#include <string>

namespace openGGL {

/**
 * Default implementations for application event handlers.
 */
#ifndef OPENGGL_APP_EVENTS_DEFAULT_IMMPLEMENTATION_DISABLED
#ifndef OPENGGL_APP_EVENTS_DEFAULT_KEYPRESS_IMPLEMENTATION_DISABLED
void App::keyPressed(const int key) const {
  if (isDebugEventFlagOn(DEBUG_KEY_PRESS)) {
    std::cout << "Key Pressed: " << glfwGetKeyName(key, 0) << std::endl;
  }
}
#endif

#ifndef OPENGGL_APP_EVENTS_DEFAULT_KEYRELEASED_IMPLEMENTATION_DISABLED
void App::keyReleased(const int key) const {
  if (isDebugEventFlagOn(DEBUG_KEY_RELEASE)) {
    std::cout << "Key Released: " << glfwGetKeyName(key, 0) << std::endl;
  }
}
#endif

#ifndef OPENGGL_APP_EVENTS_DEFAULT_MOUSEENTERED_IMPLEMENTATION_DISABLED
void App::mouseEntered() const {
  if (isDebugEventFlagOn(DEBUG_MOUSE_ENTER)) {
    std::cout << "Mouse entered Window" << std::endl;
  }
}
#endif

#ifndef OPENGGL_APP_EVENTS_DEFAULT_MOUSEEXITED_IMPLEMENTATION_DISABLED
void App::mouseExited() const {
  if (isDebugEventFlagOn(DEBUG_MOUSE_EXIT)) {
    std::cout << "Mouse exited Window" << std::endl;
  }
}
#endif

#ifndef OPENGGL_APP_EVENTS_DEFAULT_MOUSEMOVED_IMPLEMENTATION_DISABLED
void App::mouseMoved(const double mouseX, const double mouseY) const {
  if (isDebugEventFlagOn(DEBUG_MOUSE_MOVE)) {
    std::cout << "Mouse: (" << mouseX << ", " << mouseY << ")" << std::endl;
  }
}
#endif

#ifndef OPENGGL_APP_EVENTS_DEFAULT_MOUSEPRESSED_IMPLEMENTATION_DISABLED
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
#endif

#ifndef OPENGGL_APP_EVENTS_DEFAULT_MOUSERELEASED_IMPLEMENTATION_DISABLED
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
#endif

#ifndef OPENGGL_APP_EVENTS_DEFAULT_MOUSESCROLLED_IMPLEMENTATION_DISABLED
void App::mouseScrolled(const double xOffset, const double yOffset) const {
  if (isDebugEventFlagOn(DEBUG_MOUSE_SCROLL)) {
    std::cout << "Mouse scroll: (" << xOffset << ", " << yOffset << ")"
              << std::endl;
  }
}
#endif
#endif // OPENGGL_APP_EVENTS_DEFAULT_IMMPLEMENTATION_DISABLED

} // namespace openGGL

#endif // INCLUDE_APP_EVENTS_CPP_
