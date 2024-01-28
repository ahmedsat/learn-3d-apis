#include "gl-frame/frame.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils/file.h"

int fps;

GLuint create_VBO(GLsizeiptr size, const void *data, GLenum usage)
{
  GLuint vbo;
  glGenBuffers(1, &vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return vbo;
}

double lastTime;
int frames;
void update_fps()
{
  double currentTime = glfwGetTime();
  frames++;
  if (currentTime - lastTime >= 1.0)
  {
    fps = frames;
    frames = 0;
    lastTime += 1.0;
  }
}

GLuint create_shader_from_string(GLenum type, const char *str)
{
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &str, NULL);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
  {
    fprintf(stderr, "================\n");
    fprintf(stderr, "%s\n", str);
    fprintf(stderr, "================\n");
    return 0;
  }
  return shader;
}

GLuint create_shader_from_file(GLenum type, const char *file_path)
{
  char *str = read_file_as_string(file_path);
  return create_shader_from_string(type, str);
}

GLuint create_shader_program(int count, GLuint *shaders)
{
  GLuint program = glCreateProgram();

  for (int i = 0; i < count; i++)
  {
    glAttachShader(program, shaders[i]);
  }

  glLinkProgram(program);

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE)
  {
    return 0;
  }

  for (int i = 0; i < count; i++)
  {
    glDetachShader(program, shaders[i]);
  }

  return program;
}