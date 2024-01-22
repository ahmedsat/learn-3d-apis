#include <stdio.h>
#include <stdlib.h>

// #include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

int main()
{
    GLFWwindow *window;

    // glewExperimental = true;
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Play Ground", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}