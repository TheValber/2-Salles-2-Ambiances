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
#include "../include/FPSCamera.hpp"

using namespace glimac;

int window_width = 1200;
int window_height = 800;

auto fpsCamera = FPSCamera(0.07f, 0.2f, 0.3f);

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

static void cursor_position_callback(GLFWwindow * /*window*/, double xpos, double ypos)
{
    fpsCamera.rotateLeft(xpos - lastX);
    fpsCamera.rotateUp(-(ypos - lastY));
    lastX = xpos;
    lastY = ypos;
}

static void size_callback(GLFWwindow * /*window*/, int width, int height)
{
    window_width = width;
    window_height = height;
}

static void moveCamera(GLFWwindow *window, const Room &room)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        fpsCamera.moveFront(1, room);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        fpsCamera.moveFront(-1, room);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        fpsCamera.moveRight(-1, room);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        fpsCamera.moveRight(1, room);
    }
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
    glfwSetCursorPosCallback(window, &cursor_position_callback);

    lastX = window_width / 2;
    lastY = window_height / 2;

    Room1 room1(testShaderLocations1);
    if (!room1.initTextures(applicationPath.dirPath()))
    {
        std::cerr << "Error while loading textures" << std::endl;
        return -1;
    }
    Room2 room2(testShaderLocations2);
    if (!room2.initTextures(applicationPath.dirPath()))
    {
        std::cerr << "Error while loading textures" << std::endl;
        return -1;
    }

    glm::mat4 defaultProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / window_height, 0.1f, 100.f);
    glm::mat4 defaultMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (fpsCamera.getPosition().x < 0)
        {
            // In the Room 1
            moveCamera(window, room1);
            program1.use();
            glClearColor(0.f, 0.25f, 0.5f, 1.f);
        }
        else
        {
            // In the Room 2
            moveCamera(window, room2);
            program2.use();
            glClearColor(0.f, 0.5f, 1.f, 1.f);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto cameraViewMatrix = fpsCamera.getViewMatrix();
        glm::mat4 ProjMatrix = defaultProjMatrix;
        glm::mat4 MVMatrix = defaultMVMatrix * cameraViewMatrix;

        room1.draw(ProjMatrix, MVMatrix);
        room2.draw(ProjMatrix, MVMatrix);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    room1.deleteRoom();
    room2.deleteRoom();

    glfwTerminate();
    return 0;
}
