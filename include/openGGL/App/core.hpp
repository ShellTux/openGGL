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
#ifndef INCLUDE_APP_CORE_HPP_
#define INCLUDE_APP_CORE_HPP_

#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>

// Defines the various debug event flags for the application.
#define DEBUG_EVENT_FLAGS                                                      \
  FLAG(DEBUG_KEY_PRESS, 1)                                                     \
  FLAG(DEBUG_KEY_RELEASE, 2)                                                   \
  FLAG(DEBUG_MOUSE_MOVE, 3)                                                    \
  FLAG(DEBUG_MOUSE_PRESS, 4)                                                   \
  FLAG(DEBUG_MOUSE_RELEASE, 5)                                                 \
  FLAG(DEBUG_MOUSE_ENTER, 6)                                                   \
  FLAG(DEBUG_MOUSE_EXIT, 7)                                                    \
  FLAG(DEBUG_MOUSE_SCROLL, 8)

namespace openGGL {

/**
 * Main application class to manage the window and input events.
 */
class App {
public:
  App() = default;

  /**
   * Constructor with specified window dimensions.
   * @param width  The width of the window.
   * @param height The height of the window.
   */
  App(const int width, const int height);

  /**
   * Constructor with specified dimensions and title.
   * @param width  The width of the window.
   * @param height The height of the window.
   * @param title  The title of the window.
   */
  App(const int width, const int height, const std::string &title);

  App(App &&) = default;
  App(const App &) = default;
  App &operator=(App &&) = default;
  App &operator=(const App &) = default;
  ~App();

  /**
   * Enum representing various debug event flags for application state.
   */
  enum DebugEventFlag {
#define FLAG(KEY, OFFSET_BIT) KEY = 1 << (OFFSET_BIT),
    DEBUG_EVENT_FLAGS
#undef FLAG

        DEBUG_ALL = 0
#define FLAG(KEY, OFFSET_BIT) | (1 << (OFFSET_BIT))
    DEBUG_EVENT_FLAGS
#undef FLAG
    ,
  };

  /**
   * Enum representing display modes.
   */
  enum class DisplayMode {
    /**
     * 2D unit display mode.
     *
     * This mode represents a 2D coordinate system where:
     * - The +X axis points to the right.
     * - The +Y axis points up.
     * - The (O)rigin (0,0) is at the center of the screen.
     *
     *
     *               {--------Screen Width------}
     *    (-1, 1) <- +--------------------------+ {
     *               |            ^+Y           | |
     *               |            |             | |
     *               |            |             | | Screen
     *               |            O--->+X       | | Height
     *               |                          | |
     *               |                          | |
     *               |                          | |
     *               +--------------------------+ } -> (1, -1)
     *
     * This mode is suitable for rendering 2D graphics without depth.
     */
    Unit2D,

    /**
     * 3D unit display mode.
     *
     * This mode represents a 3D coordinate system where:
     * - The +X axis points to the right.
     * - The +Y axis points up.
     * - The +Z axis comes out of the screen towards the viewer.
     * - The (O)rigin (0,0,0) is at the center of the screen.
     *
     *               {--------Screen Width------}
     * (-1, 1, 0) <- +--------------------------+ {
     *               |            ^+Y           | |
     *               |            |             | |
     *               |            |             | | Screen
     *               |            O--->+X       | | Height
     *               |           /              | |
     *               |          /+Z             | |
     *               |                          | |
     *               +--------------------------+ } -> (1, -1, 0)
     *
     * This mode is suitable for rendering 3D graphics.
     */
    Unit3D,

    /**
     * 2D screen display mode.
     *
     * This mode represents a 2D screen coordinate system where:
     * - The +X axis points to the right.
     * - The +Y axis points down.
     * - The (O)rigin (0,0) is at the top left corner of the screen.
     *
     *               {--------Screen Width------}
     *     (0, 0) <- O--------------------------+ {
     *               |                          | |
     *               |            +--->+X       | |
     *               |            |             | | Screen
     *               |            |             | | Height
     *               |            |+Y           | |
     *               |                          | |
     *               |                          | |
     *               +--------------------------+ } -> (width, height)
     *
     *
     *
     * This mode is typically used for GUI layouts and 2D graphics on the
     * screen.
     */
    Screen2D,

    /**
     * 3D screen display mode.
     *
     * This mode represents a 3D screen coordinate system where:
     * - The +X axis points to the right.
     * - The +Y axis points down.
     * - The +Z axis comes out of the screen towards the viewer.
     * - The (O)rigin (0,0) is at the top left corner of the screen.
     *
     *               {--------Screen Width------}
     *  (0, 0, 0) <- O--------------------------+ {
     *               |                          | |
     *               |            +--->+X       | |
     *               |           /|             | | Screen
     *               |          / |             | | Height
     *               |       +Z/  |+Y           | |
     *               |                          | |
     *               |                          | |
     *               +--------------------------+ } -> (width, height, 0)
     *
     * This mode is suitable for rendering 3D graphics on the screen.
     */
    Screen3D,
  };

  using WindowAppMap = std::unordered_map<GLFWwindow *, const App *>;

  /**
   * Sets a specific debug event flag.
   * @param debugEventFlag The debug event flag to set.
   * @return Reference to this application.
   */
  App &setDebugEventFlag(const DebugEventFlag debugEventFlag);

  /**
   * Unsets a specific debug event flag.
   * @param debugEventFlag The debug event flag to unset.
   * @return Reference to this application.
   */
  App &unsetDebugEventFlag(const DebugEventFlag debugEventFlag);

  /**
   * Clears all debug event flags.
   * @return Reference to this application.
   */
  App &clearDebugEventFlags();

  /**
   * Sets a framebuffer size callback function.
   * @param callback The callback function to set.
   * @return Reference to this application.
   */
  App &setFramebufferSizeCallback(void (*callback)(GLFWwindow *, int, int));

  /**
   * Sets a framebuffer size callback with a display mode.
   * @param mode The display mode to set.
   * @return Reference to this application.
   */
  App &setFramebufferSizeCallback(const DisplayMode mode);

  /** Retrieves all application instances.
   * @return A map of GLFW windows to Application pointers.
   */
  static WindowAppMap getAllApps();

  /**
   * Called when a key is pressed.
   *
   * @param key The key code of the pressed key.
   */
  void keyPressed(const int key) const;

  /**
   * Called when a key is released.
   *
   * @param key The key code of the released key.
   */
  void keyReleased(const int key) const;

  /**
   * Called when the mouse is dragged.
   *
   * @param x The current x position of the mouse.
   * @param y The current y position of the mouse.
   * @param button The button used to drag the mouse.
   */
  void mouseDragged(const int x, const int y, const int button) const;

  /** Called when the mouse enters the window. */
  void mouseEntered() const;

  /** Called when the mouse exits the window. */
  void mouseExited() const;

  /**
   * Called when the mouse is moved.
   *
   * @param mouseX The new x position of the mouse.
   * @param mouseY The new y position of the mouse.
   */
  void mouseMoved(const double mouseX, const double mouseY) const;

  /**
   * Called when a mouse button is pressed.
   *
   * @param button The button code of the pressed mouse button.
   * @param mods Any modifier keys that were active during the press.
   */
  void mousePressed(const int button, const int mods) const;

  /**
   * Called when a mouse button is released.
   *
   * @param button The button code of the released mouse button.
   * @param mods Any modifier keys that were active during the release.
   */
  void mouseReleased(const int button, const int mods) const;

  /**
   * Called when the mouse wheel is scrolled.
   *
   * @param xOffset The offset of the scroll along the x-axis.
   * @param yOffset The offset of the scroll along the y-axis.
   */
  void mouseScrolled(const double xOffset, const double yOffset) const;

  /**
   * Called when the window is resized.
   *
   * @param width  The new width of the window.
   * @param height The new height of the window.
   */
  void windowResized(const size_t width, const size_t height) const;

  /**
   * Returns the current mouse position.
   * @return A pair of the mouse X and Y coordinates.
   */
  [[nodiscard]] std::pair<double, double> getMousePos() const;

  /**
   * Returns the current window size.
   * @return A pair of the window width and height.
   */
  [[nodiscard]] std::pair<int, int> getWindowSize() const;

  /** Initializes the OpenGL context and enter the drawing loop. */
  void init();

  /** Holds all App instances. */
  static WindowAppMap allApps;

private:
  /** Updates the application state. */
  void update();

  /** Sets up the application state. */
  void setup();

  /** Draws the application content. */
  void draw();

  /** Internal Initialization. */
  void mInit();

  /** Internal Setup. */
  void mSetup();

  /** Internal Wrap for draw. */
  void mDraw();

  /**
   * Checks if a specific debug event flag is currently on.
   * @param debugEventFlag The debug event flag to check.
   * @return True if the flag is on, false otherwise.
   */
  [[nodiscard]] bool
  isDebugEventFlagOn(const DebugEventFlag debugEventFlag) const;

  static constexpr const char *windowClass = "OpenGL"; // Window class name
  static constexpr int defaultWidth = 600;             // Default window width
  static constexpr int defaultHeight = 600;            // Default window height

  GLFWwindow *window = NULL;    // GLFW window pointer
  uint64_t debugEventFlags = 0; // Bitmask for debug event flags
  bool enabled3D = false;       // Flag to indicate if 3D mode is enabled
};

} // namespace openGGL

#endif // INCLUDE_APP_CORE_HPP_
