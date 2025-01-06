// Glass.cpp

#include "../include/Glass.hpp"
#include <iostream>
#include "../include/vertexAttr.hpp"
#include "../include/utils.hpp"
#include <algorithm>

Glass::Glass(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{

    _position = position;
    _rotation = rotation;
    _scale = scale;

    for (int i = 0; i < 5; i++)
    {
        _glassVAOs.push_back(GlassVAO());
        _glassVAOs[i].i = i;
    }

    // Base
    insertCubeVertices(glm::vec3(12.5f, 1.75f, 4.f), glm::vec3(2.99f, 1.49f, 0.1f), _glassVAOs[0].vertices);
    _glassVAOs[0].position = glm::vec3(12.5f, 1.75f, 4.f);
    insertCubeVertices(glm::vec3(17.5f, 1.75f, 4.f), glm::vec3(2.99f, 1.49f, 0.1f), _glassVAOs[1].vertices);
    _glassVAOs[1].position = glm::vec3(17.5f, 1.75f, 4.f);
    insertCubeVertices(glm::vec3(18.f, 1.75f, 0.f), glm::vec3(3.99f, 1.49f, 0.1f), _glassVAOs[2].vertices);
    _glassVAOs[2].position = glm::vec3(18.f, 1.75f, 0.f);

    insertCubeVertices(glm::vec3(15.f, 1.5f, 11.f), glm::vec3(0.1f, 3.f, 2.f), _glassVAOs[3].vertices);
    _glassVAOs[3].position = glm::vec3(15.f, 1.5f, 11.f);
    insertCubeVertices(glm::vec3(18.f, 1.5f, 11.f), glm::vec3(0.1f, 3.f, 2.f), _glassVAOs[4].vertices);
    _glassVAOs[4].position = glm::vec3(18.f, 1.5f, 11.f);

    for (int i = 0; i < 5; i++)
    {
        _glassVAOs[i].vertexCount = _glassVAOs[i].vertices.size();
    }

    _Kd = glm::vec3(0.1f, 0.1f, 0.1f);
    _Ks = glm::vec3(1.f, 1.f, 1.f);
    _Shininess = 200.f;
}

void Glass::initVBO()
{
    for (size_t i = 0; i < _glassVAOs.size(); i++)
    {
        glGenBuffers(1, &_glassVAOs[i].vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _glassVAOs[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, _glassVAOs[i].vertexCount * sizeof(ShapeVertex), _glassVAOs[i].vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Glass::initVAO()
{
    for (size_t i = 0; i < _glassVAOs.size(); i++)
    {
        glGenVertexArrays(1, &_glassVAOs[i].vao);
        glBindVertexArray(_glassVAOs[i].vao);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
        glBindBuffer(GL_ARRAY_BUFFER, _glassVAOs[i].vbo);
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position));
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));
        glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void Glass::setTexture(GLuint texture)
{
    _texture = texture;
}

void Glass::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const
{
    glm::mat4 inverseMVMatrix = glm::inverse(MVMatrix);
    glm::vec3 cameraPosition = glm::vec3(inverseMVMatrix[3][0], inverseMVMatrix[3][1], inverseMVMatrix[3][2]);

    std::vector<GlassVAO> glassVAOcopy = std::vector<GlassVAO>(_glassVAOs);

    std::sort(glassVAOcopy.begin(), glassVAOcopy.end(), [cameraPosition](const GlassVAO &a, const GlassVAO &b)
              { return glm::distance(a.position, cameraPosition) > glm::distance(b.position, cameraPosition); });

    glm::mat4 MVMat = MVMatrix * glm::translate(glm::mat4(1), _position);
    MVMat = MVMat * glm::rotate(glm::mat4(1), glm::radians(_rotation.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.y), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    MVMat = MVMat * glm::scale(glm::mat4(1), _scale);
    glm::mat4 NormalMat = glm::transpose(glm::inverse(MVMat));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniform3f(uniformLocations.uKdLocation, _Kd.x, _Kd.y, _Kd.z);
    glUniform3f(uniformLocations.uKsLocation, _Ks.x, _Ks.y, _Ks.z);
    glUniform1f(uniformLocations.uShininessLocation, _Shininess);

    glUniformMatrix4fv(uniformLocations.uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMat));
    glUniformMatrix4fv(uniformLocations.uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMat));
    glUniformMatrix4fv(uniformLocations.uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMat));

    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(uniformLocations.uTextureLocation, 0);

    for (const auto &glassVAO : glassVAOcopy)
    {
        glBindVertexArray(glassVAO.vao);
        glDrawArrays(GL_TRIANGLES, 0, glassVAO.vertexCount);
        glBindVertexArray(0);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
}

void Glass::deleteDrawable()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}
