#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/FilePath.hpp>
#include <iostream>

#include "../include/utils.hpp"
#include "../include/DrawableSquare.hpp"

using namespace glimac;

int window_width = 1200;
int window_height = 800;

const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_NORMAL = 1;
const GLuint VERTEX_ATTR_TEXCOORDS = 2;

static void key_callback(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (action == GLFW_PRESS && key == GLFW_KEY_F)
    {
        static bool isWireframe = false;
        if (isWireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            std::cout << "FILL" << std::endl;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            std::cout << "WIREFRAME" << std::endl;
        }
        isWireframe = !isWireframe;
    }
}

static void size_callback(GLFWwindow * /*window*/, int width, int height)
{
    window_width = width;
    window_height = height;
}

int main(int /*argc*/, char **argv)
{
    GLFWwindow *window;

    if (!initializeGLFW(window, window_width, window_height))
    {
        return -1;
    }

    FilePath applicationPath(argv[0]);

    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowSizeCallback(window, &size_callback);

    DrawableSquare square(2.f, 4.f, 0.f, 0.f);
    square.initVBO();
    square.initVAO(VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXCOORDS);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

    return 0;
}
