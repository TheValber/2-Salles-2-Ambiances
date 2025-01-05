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
#include "../include/Skybox.hpp"

using namespace glimac;

int window_width = 1200;
int window_height = 800;

auto fpsCamera = FPSCamera(0.07f, 0.2f, 0.3f);

double lastX = 0;
double lastY = 0;

bool isLightOn = true;
bool isAnimated = true;

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
    else if (action == GLFW_PRESS && key == GLFW_KEY_E)
    {
        isLightOn = !isLightOn;
    }
    else if (action == GLFW_PRESS && key == GLFW_KEY_Q)
    {
        isAnimated = !isAnimated;
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

    Program program1 = loadProgram(applicationPath.dirPath() + "/shaders/room1.vs.glsl",
                                   applicationPath.dirPath() + "/shaders/room1.fs.glsl");
    program1.use();
    UniformLocations uniformLocations1(program1);

    Program program2 = loadProgram(applicationPath.dirPath() + "/shaders/room2.vs.glsl",
                                   applicationPath.dirPath() + "/shaders/room2.fs.glsl");
    program2.use();
    UniformLocations uniformLocations2(program2);

    Program skyboxProgram = loadProgram(applicationPath.dirPath() + "/shaders/skybox.vs.glsl",
                                        applicationPath.dirPath() + "/shaders/skybox.fs.glsl");
    skyboxProgram.use();
    UniformLocations skyboxUniformLocations(skyboxProgram);

    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowSizeCallback(window, &size_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);

    lastX = window_width / 2;
    lastY = window_height / 2;

    Room1 room1 = Room1();
    if (!room1.initTextures(applicationPath.dirPath()))
    {
        std::cerr << "Error while loading textures" << std::endl;
        return -1;
    }
    Room2 room2 = Room2();
    if (!room2.initTextures(applicationPath.dirPath()))
    {
        std::cerr << "Error while loading textures" << std::endl;
        return -1;
    }

    Skybox skybox = Skybox(applicationPath.dirPath());

    glm::mat4 defaultProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / window_height, 0.1f, 100.f);
    glm::mat4 defaultMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

    UniformLocations uniformLocations = uniformLocations1;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        auto cameraViewMatrix = fpsCamera.getViewMatrix();
        glm::mat4 ProjMatrix = defaultProjMatrix;
        glm::mat4 MVMatrix = defaultMVMatrix * cameraViewMatrix;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int roomNb = fpsCamera.getPosition().x < 0 ? 1 : 2;
        skybox.setActualTexture(roomNb);

        skyboxProgram.use();
        skybox.draw(ProjMatrix, cameraViewMatrix, skyboxUniformLocations);

        glClearColor(1.f, 0.95f, 0.95f, 1.f);

        if (roomNb == 1)
        {
            // In the Room 1
            moveCamera(window, room1);
            program1.use();
            uniformLocations = uniformLocations1;
            room1.setLightOn(isLightOn);
        }
        else
        {
            // In the Room 2
            moveCamera(window, room2);
            program2.use();
            uniformLocations = uniformLocations2;
        }

        room1.draw(ProjMatrix, MVMatrix, uniformLocations, roomNb == 1);
        room2.draw(ProjMatrix, MVMatrix, uniformLocations, roomNb == 2);

        room2.drawGlass(ProjMatrix, MVMatrix, uniformLocations);

        if (isAnimated)
        {
            room1.animate();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    room1.deleteRoom();
    room2.deleteRoom();
    skybox.deleteDrawable();

    glfwTerminate();
    return 0;
}
