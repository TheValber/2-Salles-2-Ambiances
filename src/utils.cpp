// utils.cpp
#include "../include/utils.hpp"

bool initializeGLFW(GLFWwindow *&window, int window_width, int window_height)
{
    /* Inititalize glfw library */
    if (!glfwInit())
    {
        return false;
    }

    /* Create a window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    window = glfwCreateWindow(window_width, window_height, "2 Salles 2 Ambiances", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return false;
    }

    /* Enable depth test */
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

glm::vec2 rotateTexCoords(const glm::vec2 &texCoords, float angle)
{
    glm::vec2 rotatedTexCoords;
    rotatedTexCoords.x = texCoords.x * cos(angle) - texCoords.y * sin(angle);
    rotatedTexCoords.y = texCoords.x * sin(angle) + texCoords.y * cos(angle);
    return rotatedTexCoords;
}
