// Skybox.cpp

#include "../include/Skybox.hpp"
#include <iostream>
#include "../include/vertexAttr.hpp"
#include "../include/utils.hpp"

Skybox::Skybox(FilePath dirPath)
{
    float cube[] = {
        // Positions
        -1.0f, 1.0f, -1.0f, // Face arrière
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f, // Face avant
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f, // Face droite
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f, // Face gauche
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f, // Face du haut
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f, // Face du bas
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    for (int i = 0; i < 36; i++)
    {
        _vertices.push_back(glm::vec3(cube[i * 3], cube[i * 3 + 1], cube[i * 3 + 2]));
    }

    m_nVertexCount = _vertices.size();

    initVBO();
    initVAO();

    _room1Texture = loadCubemap({dirPath.dirPath() + "/assets/textures/skybox/1right.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/1left.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/1top.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/1bottom.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/1front.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/1back.jpg"});

    _room2Texture = loadCubemap({dirPath.dirPath() + "/assets/textures/skybox/2right.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/2left.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/2top.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/2bottom.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/2front.jpg",
                                 dirPath.dirPath() + "/assets/textures/skybox/2back.jpg"});
}

void Skybox::initVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Skybox::initVAO()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Skybox::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const
{
    glm::mat4 view = glm::mat4(glm::mat3(MVMatrix));
    glm::mat4 projection = ProjMatrix;

    glUniformMatrix4fv(uniformLocations.uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(uniformLocations.uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));

    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(_vao);
    if (_actualTexture == 1)
        glBindTexture(GL_TEXTURE_CUBE_MAP, _room1Texture);
    else
        glBindTexture(GL_TEXTURE_CUBE_MAP, _room2Texture);
    glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void Skybox::deleteDrawable()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
    glDeleteTextures(1, &_room1Texture);
    glDeleteTextures(1, &_room2Texture);
}
