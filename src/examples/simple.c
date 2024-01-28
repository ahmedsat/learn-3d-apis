#include "gl-frame/frame.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void init() {}
void gl_init() {}

void input()
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}

void update() {}
void render() {}
void close() {}