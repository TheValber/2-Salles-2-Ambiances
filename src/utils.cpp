// utils.cpp
#include "../include/utils.hpp"
#include <src/stb_image.h>
#include <iostream>

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
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(scale.z, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(scale.z, scale.y)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(scale.z, scale.y)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x - demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(-1, 0, 0), glm::vec2(0, scale.y)});

    // Droite
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(1, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z + demiScale.z), glm::vec3(1, 0, 0), glm::vec2(scale.z, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(1, 0, 0), glm::vec2(scale.z, scale.y)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y - demiScale.y, position.z - demiScale.z), glm::vec3(1, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z + demiScale.z), glm::vec3(1, 0, 0), glm::vec2(scale.z, scale.y)});
    vertices.push_back(ShapeVertex{glm::vec3(position.x + demiScale.x, position.y + demiScale.y, position.z - demiScale.z), glm::vec3(1, 0, 0), glm::vec2(0, scale.y)});
}

void insertSphereVertices(glm::vec3 position, float radius, std::vector<ShapeVertex> &vertices, int latitudeBands, int longitudeBands, bool inverseNormal)
{
    std::vector<ShapeVertex> sphereVertices;

    for (int latNumber = 0; latNumber <= latitudeBands; ++latNumber)
    {
        float theta = latNumber * glm::pi<float>() / latitudeBands;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int longNumber = 0; longNumber <= longitudeBands; ++longNumber)
        {
            float phi = longNumber * 2 * glm::pi<float>() / longitudeBands;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            glm::vec3 normal = glm::vec3(cosPhi * sinTheta, cosTheta, sinPhi * sinTheta);
            glm::vec3 vertexPosition = position + radius * normal;
            glm::vec2 texCoords = glm::vec2(1.0f - (float)longNumber / longitudeBands, 1.0f - (float)latNumber / latitudeBands);

            sphereVertices.push_back(ShapeVertex{vertexPosition, normal * (inverseNormal ? -1.f : 1.f), texCoords});
        }
    }

    for (int latNumber = 0; latNumber < latitudeBands; ++latNumber)
    {
        for (int longNumber = 0; longNumber < longitudeBands; ++longNumber)
        {
            int first = (latNumber * (longitudeBands + 1)) + longNumber;
            int second = first + longitudeBands + 1;

            vertices.push_back(sphereVertices[first]);
            vertices.push_back(sphereVertices[second]);
            vertices.push_back(sphereVertices[first + 1]);

            vertices.push_back(sphereVertices[second]);
            vertices.push_back(sphereVertices[second + 1]);
            vertices.push_back(sphereVertices[first + 1]);
        }
    }
}

GLuint loadCubemap(std::vector<std::string> filesNames)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < filesNames.size(); i++)
    {
        unsigned char *data = stbi_load(filesNames[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cerr << "Cubemap texture failed to load at path: " << filesNames[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
