#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl-frame/frame.h"

void init();
void gl_init();
void input();
void update();
void render();
void close();
void loop();
void resize(GLFWwindow *window, int width, int height);

GLFWwindow *window;
int width = 800;
int height = 600;
char *title = "no title";

int main(void)
{

  if (!glfwInit())
    return -1;

  init();

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, resize);

  glfwMakeContextCurrent(window);

  glewExperimental = true; // ? Needed in core profile
  if (glewInit() != GLEW_OK)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  glViewport(0, 0, width, height);

  // ? VAO
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  gl_init();

  while (!glfwWindowShouldClose(window))
  {

    update_fps();

    glClear(GL_COLOR_BUFFER_BIT);

    loop();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  close();

  glfwTerminate();
  return 0;
}

void resize(GLFWwindow *window, int width, int height)
{
  (void)window;
  glViewport(0, 0, width, height);
}

void loop()
{
  input();
  update();
  render();
}