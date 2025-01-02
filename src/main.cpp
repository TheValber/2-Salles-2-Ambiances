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

    // TEMPORARY //////////////
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "/shaders/test.vs.glsl",
                                  applicationPath.dirPath() + "/shaders/test.fs.glsl");
    program.use();

    GLint uMVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrixLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint uTextureLocation = glGetUniformLocation(program.getGLId(), "uTexture");
    //////////////////////

    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowSizeCallback(window, &size_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);

    DrawableSquare square(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(2.f, 4.f, 1.f));
    square.initVBO();
    square.initVAO(VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXCOORDS);
    square.setLocations(uMVPMatrixLocation, uMVMatrixLocation, uNormalMatrixLocation, uTextureLocation);

    DrawableSquare square2(glm::vec3(-11.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(20.f, 24.f, 1.f));
    square2.initVBO();
    square2.initVAO(VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXCOORDS);
    square2.setLocations(uMVPMatrixLocation, uMVMatrixLocation, uNormalMatrixLocation, uTextureLocation);

    DrawableSquare square3(glm::vec3(11.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(20.f, 24.f, 1.f));
    square3.initVBO();
    square3.initVAO(VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXCOORDS);
    square3.setLocations(uMVPMatrixLocation, uMVMatrixLocation, uNormalMatrixLocation, uTextureLocation);

    glm::mat4 defaultProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / window_height, 0.1f, 100.f);
    glm::mat4 defaultMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        auto cameraViewMatrix = trackballCamera.getViewMatrix();
        glm::mat4 ProjMatrix = defaultProjMatrix;
        glm::mat4 MVMatrix = defaultMVMatrix * cameraViewMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glClearColor(.1f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        square.draw(ProjMatrix, MVMatrix, NormalMatrix);
        square2.draw(ProjMatrix, MVMatrix, NormalMatrix);
        square3.draw(ProjMatrix, MVMatrix, NormalMatrix);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

    return 0;
}
