#ifndef _GL_FRAME_H
#define _GL_FRAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern GLFWwindow *window;
extern int width;
extern int height;
extern char *title;

// internals
extern int fps;

void update_fps();

GLuint create_VBO(GLsizeiptr size, const void *data, GLenum usage);

GLuint create_shader_from_string(GLenum type, const char *str);
GLuint create_shader_from_file(GLenum type, const char *file_path);
GLuint create_shader_program(int count, GLuint *shaders);

#endif //_GL_FRAME_H