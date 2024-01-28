#include "gl-frame/frame.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const float vertexPositions[] = {
    0.0f, 0.5f, 0.0f, 1.0f,   //
    0.5f, -0.5f, 0.0f, 1.0f,  //
    -0.5f, -0.5f, 0.0f, 1.0f, //
};

GLuint shader_program, position_VBO;

int err;

void init()
{
  title = "simple";

  glfwWindowHint(GLFW_RESIZABLE, false);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void gl_init()
{
  position_VBO = create_VBO(sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
  GLuint vert = create_shader_from_file(GL_VERTEX_SHADER, "shaders/simple.vert");
  if (!vert)
    err = 1;
  GLuint frag = create_shader_from_file(GL_FRAGMENT_SHADER, "shaders/simple.frag");
  if (!frag)
    err = 1;

  GLuint shaders[] = {vert, frag};

  shader_program = create_shader_program(2, shaders);
  if (!shader_program)
    err = 1;
}

void input()
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void update()
{
  if (err)
    glfwSetWindowShouldClose(window, true);
  printf("\r%i fps", fps);
}

void render()
{

  glUseProgram(shader_program);

  glBindBuffer(GL_ARRAY_BUFFER, position_VBO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glUseProgram(0);
}
void close() {}