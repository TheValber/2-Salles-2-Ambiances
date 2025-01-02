#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/FilePath.hpp>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/glm.hpp>

#include "../include/utils.hpp"
#include "../include/DrawableSquare.hpp"
#include "../include/UniformLocations.hpp"
#include "../include/Room1.hpp"
#include "../include/Room2.hpp"

using namespace glimac;

int window_width = 1200;
int window_height = 800;

const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_NORMAL = 1;
const GLuint VERTEX_ATTR_TEXCOORDS = 2;

auto trackballCamera = TrackballCamera();
bool leftClick = false;
double lastX = 0;
double lastY = 0;

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
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        isWireframe = !isWireframe;
    }
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int /*mods*/)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        leftClick = true;
        glfwGetCursorPos(window, &lastX, &lastY);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        leftClick = false;
    }
}

static void scroll_callback(GLFWwindow * /*window*/, double /*xoffset*/, double yoffset)
{
    trackballCamera.moveFront(-yoffset * 0.1f);
}

static void cursor_position_callback(GLFWwindow * /*window*/, double xpos, double ypos)
{
    if (leftClick)
    {
        trackballCamera.rotateLeft((xpos - lastX));
        trackballCamera.rotateUp((ypos - lastY));
        lastX = xpos;
        lastY = ypos;
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

    // TEMPORARY 1 //////////////
    Program program1 = loadProgram(applicationPath.dirPath() + "/shaders/test1.vs.glsl",
                                   applicationPath.dirPath() + "/shaders/test1.fs.glsl");
    program1.use();

    UniformLocations testShaderLocations1(program1);
    //////////////////////

    // TEMPORARY 2 //////////////
    Program program2 = loadProgram(applicationPath.dirPath() + "/shaders/test2.vs.glsl",
                                   applicationPath.dirPath() + "/shaders/test2.fs.glsl");
    program2.use();

    UniformLocations testShaderLocations2(program2);
    //////////////////////

    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowSizeCallback(window, &size_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);

    Room1 room1(testShaderLocations1);
    Room2 room2(testShaderLocations2);

    glm::mat4 defaultProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / window_height, 0.1f, 100.f);
    glm::mat4 defaultMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        auto cameraViewMatrix = trackballCamera.getViewMatrix();
        glm::mat4 ProjMatrix = defaultProjMatrix;
        glm::mat4 MVMatrix = defaultMVMatrix * cameraViewMatrix;

        glClearColor(.1f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program1.use();
        room1.draw(ProjMatrix, MVMatrix);

        program2.use();
        room2.draw(ProjMatrix, MVMatrix);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

    return 0;
}
