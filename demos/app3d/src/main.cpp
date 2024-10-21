#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <openGGL/3D/geometric-figures-unit.hpp>
#include <openGGL/App/core.hpp>
#include <string>

GLfloat scale = 1.0f;
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat angleZ = 0.0f;

namespace openGGL {

void App::update() {
  angleX += 1.3f;
  angleY += 0.9f;
  angleZ += 1.8f;
};

void App::setup() {};

void App::draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glScalef(scale, scale, scale);
  glRotatef(angleX, 1, 0, 0);
  glRotatef(angleY, 0, 1, 0);
  glRotatef(angleZ, 0, 0, 1);
  openGGL::GeometricFigures3D::Unit::Cube();
};

} // namespace openGGL

int main() {
  openGGL::App app{600, 600, "app demo"};
  app.setDebugEventFlag(openGGL::App::DEBUG_KEY_PRESS)
      .setDebugEventFlag(openGGL::App::DEBUG_MOUSE_MOVE);
  app.setFramebufferSizeCallback(openGGL::App::DisplayMode::Unit3D);
  app.init();

  return 0;
}
