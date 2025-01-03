// DrawableSquare.cpp

#include "../include/DrawableSquare.hpp"
#include <iostream>
#include "../include/vertexAttr.hpp"

DrawableSquare::DrawableSquare(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    _position = position;
    _rotation = rotation;
    _scale = scale;

    m_Vertices.push_back(ShapeVertex{glm::vec3(-0.5f, 0, -0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(0.5f, 0, -0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(0.5f, 0, 0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 1)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-0.5f, 0, -0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(0.5f, 0, 0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 1)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-0.5f, 0, 0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 1)});

    m_nVertexCount = 6;
}

void DrawableSquare::initVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DrawableSquare::initVAO()
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

void DrawableSquare::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix) const
{
    glm::mat4 MVMat = MVMatrix * glm::translate(glm::mat4(1), _position);
    MVMat = MVMat * glm::rotate(glm::mat4(1), glm::radians(_rotation.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.y), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    MVMat = MVMat * glm::scale(glm::mat4(1), _scale);
    glm::mat4 NormalMat = glm::transpose(glm::inverse(MVMat));

    glBindVertexArray(_vao);
    glUniformMatrix4fv(_uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMat));
    glUniformMatrix4fv(_uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMat));
    glUniformMatrix4fv(_uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMat));
    glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
    glBindVertexArray(0);
}
