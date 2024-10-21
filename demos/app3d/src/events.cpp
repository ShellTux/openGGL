#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <openGGL/App/core.hpp>
#define OPENGGL_APP_EVENTS_DEFAULT_KEYPRESS_IMPLEMENTATION_DISABLED
#define OPENGGL_APP_EVENTS_DEFAULT_MOUSEMOVED_IMPLEMENTATION_DISABLED
#include <openGGL/App/events.hpp>

extern GLfloat scale;

namespace openGGL {

void App::keyPressed(const int key) const {
  switch (key) {
  case GLFW_KEY_1: {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
  } break;
  case GLFW_KEY_2: {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);
  } break;
  case GLFW_KEY_3: {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
  } break;
  case GLFW_KEY_4: {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT_AND_BACK);
  } break;
  case GLFW_KEY_5: {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glCullFace(GL_BACK);
  } break;
  case GLFW_KEY_6: {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glCullFace(GL_FRONT);
  } break;
  case GLFW_KEY_7: {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
  } break;
  }
}

void App::mouseMoved(const double mouseX, const double mouseY) const {
  (void)mouseY;

  const auto [width, height] = getWindowSize();

  scale = mouseX / width;
}

} // namespace openGGL
