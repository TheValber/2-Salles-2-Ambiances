// StreetLight.cpp

#include "../include/StreetLight.hpp"
#include <iostream>
#include "../include/vertexAttr.hpp"
#include "../include/utils.hpp"

StreetLight::StreetLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{

    _position = position;
    _rotation = rotation;
    _scale = scale;

    // Base
    insertCubeVertices(glm::vec3(0.f, 0.125f, 0.f), glm::vec3(0.75f, 0.25f, 0.75f), m_Vertices);

    // Poteau
    insertCubeVertices(glm::vec3(0.f, 1.25f, 0.f), glm::vec3(0.2f, 2.5f, 0.2f), m_Vertices);

    // Chapeau Bas
    insertCubeVertices(glm::vec3(0.f, 2.625f, 0.f), glm::vec3(0.5f, 0.25f, 0.5f), m_Vertices);
    insertCubeVertices(glm::vec3(0.f, 2.875f, 0.f), glm::vec3(1.f, 0.25f, 1.f), m_Vertices);

    // Chapeau Haut
    insertCubeVertices(glm::vec3(0.f, 4.125f, 0.f), glm::vec3(1.f, 0.25f, 1.f), m_Vertices);
    insertCubeVertices(glm::vec3(0.f, 4.375f, 0.f), glm::vec3(0.5f, 0.25f, 0.5f), m_Vertices);

    // Piliers
    insertCubeVertices(glm::vec3(0.4f, 3.5f, 0.4f), glm::vec3(0.15f, 1.f, 0.15f), m_Vertices);
    insertCubeVertices(glm::vec3(-0.4f, 3.5f, 0.4f), glm::vec3(0.15f, 1.f, 0.15f), m_Vertices);
    insertCubeVertices(glm::vec3(0.4f, 3.5f, -0.4f), glm::vec3(0.15f, 1.f, 0.15f), m_Vertices);
    insertCubeVertices(glm::vec3(-0.4f, 3.5f, -0.4f), glm::vec3(0.15f, 1.f, 0.15f), m_Vertices);

    m_nVertexCount = m_Vertices.size();

    std::cout << "StreetLight created" << m_nVertexCount << std::endl;

    _Kd = glm::vec3(0.2f, 0.2f, 0.2f);
    _Ks = glm::vec3(0.8f, 0.8f, 0.8f);
    _Shininess = 75.f;

    setMinPoint();
    setMaxPoint();
}

void StreetLight::initVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void StreetLight::initVAO()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void StreetLight::setTexture(GLuint texture)
{
    _texture = texture;
}

void StreetLight::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const
{
    glm::mat4 MVMat = MVMatrix * glm::translate(glm::mat4(1), _position);
    MVMat = MVMat * glm::rotate(glm::mat4(1), glm::radians(_rotation.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.y), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    MVMat = MVMat * glm::scale(glm::mat4(1), _scale);
    glm::mat4 NormalMat = glm::transpose(glm::inverse(MVMat));

    glUniform3f(uniformLocations.uKdLocation, _Kd.x, _Kd.y, _Kd.z);
    glUniform3f(uniformLocations.uKsLocation, _Ks.x, _Ks.y, _Ks.z);
    glUniform1f(uniformLocations.uShininessLocation, _Shininess);

    glBindVertexArray(_vao);
    glUniformMatrix4fv(uniformLocations.uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMat));
    glUniformMatrix4fv(uniformLocations.uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMat));
    glUniformMatrix4fv(uniformLocations.uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMat));

    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(uniformLocations.uTextureLocation, 0);

    glDrawArrays(GL_TRIANGLES, 0, getVertexCount());

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void StreetLight::setMinPoint()
{
    glm::vec3 point(-0.1f, 0.0f, -0.1f);

    point *= _scale;

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));

    point += _position;

    _minPoint = point;
}

void StreetLight::setMaxPoint()
{
    glm::vec3 point(0.1f, 4.f, 0.1f);

    point *= _scale;

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));

    point += _position;

    _maxPoint = point;
}

bool StreetLight::isInside(glm::vec3 pos, float radius) const
{

    if (pos.x + radius < _minPoint.x || pos.x - radius > _maxPoint.x)
    {
        return false;
    }

    if (pos.z + radius < _minPoint.z || pos.z - radius > _maxPoint.z)
    {
        return false;
    }

    return true;
}

void StreetLight::deleteDrawable()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}
