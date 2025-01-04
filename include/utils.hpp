// utils.hpp
#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/glm.hpp>

/**
 * @brief Initialize GLFW library and create a window
 *
 * This function initializes the GLFW library, creates a window with the specified
 * width and height, and sets up the OpenGL context.
 *
 * @param window A reference to a pointer to a GLFWwindow object.
 * @param window_width The width of the window to be created.
 * @param window_height The height of the window to be created.
 * @return true if initialization and window creation were successful, false otherwise.
 */
bool initializeGLFW(GLFWwindow *&window, int window_width, int window_height);

glm::vec2 rotateTexCoords(const glm::vec2 &texCoords, float angle);