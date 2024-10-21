#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <openGGL/App/core.hpp>
#include <string>

namespace openGGL {

void App::update() {};
void App::setup() {};
void App::draw() {};

} // namespace openGGL

int main() {
  openGGL::App app{600, 600, "app demo"};
  app.setDebugEventFlag(openGGL::App::DEBUG_KEY_PRESS);
  app.setFramebufferSizeCallback(openGGL::App::DisplayMode::Unit3D);
  app.init();

  return 0;
}
