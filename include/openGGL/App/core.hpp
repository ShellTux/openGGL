#ifndef INCLUDE_APP_CORE_HPP_
#define INCLUDE_APP_CORE_HPP_

#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>

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

class App {
public:
  App() = default;
  App(const int width, const int height);
  App(const int width, const int height, const std::string &title);
  App(App &&) = default;
  App(const App &) = default;
  App &operator=(App &&) = default;
  App &operator=(const App &) = default;
  ~App();

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

  using WindowAppMap = std::unordered_map<GLFWwindow *, const App *>;

  App &setDebugEventFlag(const DebugEventFlag debugEventFlag);
  App &unsetDebugEventFlag(const DebugEventFlag debugEventFlag);
  App &clearDebugEventFlags();

  static WindowAppMap getAllApps();

  void keyPressed(const int key) const;
  void keyReleased(const int key) const;
  void mouseDragged(const int x, const int y, const int button) const;
  void mouseEntered() const;
  void mouseExited() const;
  void mouseMoved(const double mouseX, const double mouseY) const;
  void mousePressed(const int button, const int mods) const;
  void mouseReleased(const int button, const int mods) const;
  void mouseScrolled(const double xOffset, const double yOffset) const;
  void windowResized(const size_t width, const size_t height) const;

  [[nodiscard]] std::pair<double, double> getMousePos() const;
  [[nodiscard]] std::pair<int, int> getWindowSize() const;

  void init();

  // TODO: Change accesibility
  static WindowAppMap allApps;

private:
  void update();
  void setup();
  void draw();

  void mInit();
  void mSetup();
  void mDraw();

  [[nodiscard]] bool
  isDebugEventFlagOn(const DebugEventFlag debugEventFlag) const;

  static constexpr const char *windowClass = "OpenGL";
  static constexpr int defaultWidth = 600;
  static constexpr int defaultHeight = 600;

  GLFWwindow *window = NULL;
  uint64_t debugEventFlags = 0;
  bool enabled3D = false;
};

} // namespace openGGL

#endif // INCLUDE_APP_CORE_HPP_
