#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "../include/utils.hpp"

// using namespace glimac; // To uncomment later when glimac is included

int window_width = 1200;
int window_height = 800;

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

int main(int argc, char **argv)
{
    GLFWwindow *window;

    if (!initializeGLFW(window, window_width, window_height))
    {
        return -1;
    }

    glfwSetKeyCallback(window, &key_callback);

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
