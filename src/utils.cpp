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

void insertCubeVertices(glm::vec3 position, glm::vec3 scale, std::vector<ShapeVertex> &vertices)
{
    glm::vec3 demiScale = scale / 2.f;

    // Haut
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(0, 1, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(0, 1, 0), glm::vec2(scale.x, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(0, 1, 0), glm::vec2(scale.x, scale.z)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(0, 1, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(0, 1, 0), glm::vec2(scale.x, scale.z)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(0, 1, 0), glm::vec2(0, scale.z)});

    // Bas
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(0, -1, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(0, -1, 0), glm::vec2(scale.x, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(0, -1, 0), glm::vec2(scale.x, scale.z)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(0, -1, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(0, -1, 0), glm::vec2(scale.x, scale.z)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(0, -1, 0), glm::vec2(0, scale.z)});

    // Devant
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(0, 0, 1), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(0, 0, 1), glm::vec2(scale.x, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(0, 0, 1), glm::vec2(scale.x, scale.y)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(0, 0, 1), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(0, 0, 1), glm::vec2(scale.x, scale.y)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(0, 0, 1), glm::vec2(0, scale.y)});

    // Derrière
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(0, 0, -1), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(0, 0, -1), glm::vec2(scale.x, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(0, 0, -1), glm::vec2(scale.x, scale.y)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(0, 0, -1), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(0, 0, -1), glm::vec2(scale.x, scale.y)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(0, 0, -1), glm::vec2(0, scale.y)});

    // Gauche
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(scale.y, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(scale.y, scale.z)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(scale.y, scale.z)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(0, scale.z)});

    // Droite
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(1, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(1, 0, 0), glm::vec2(scale.y, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(1, 0, 0), glm::vec2(scale.y, scale.z)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(1, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(1, 0, 0), glm::vec2(scale.y, scale.z)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(1, 0, 0), glm::vec2(0, scale.z)});
}
