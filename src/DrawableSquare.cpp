// DrawableSquare.cpp

#include "../include/DrawableSquare.hpp"

DrawableSquare::DrawableSquare(float width, float height, float x, float y) : _width(width), _height(height), _x(x), _y(y)
{
    m_Vertices.push_back(ShapeVertex{glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), glm::vec2(1, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(1, 1, 0), glm::vec3(0, 0, 1), glm::vec2(1, 1)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(1, 1, 0), glm::vec3(0, 0, 1), glm::vec2(1, 1)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec2(0, 1)});

    m_nVertexCount = 6;
}

void DrawableSquare::initVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DrawableSquare::initVAO(GLuint vertexAttrPosition, GLuint vertexAttrNormal, GLuint vertexAttrTexCoords)
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glEnableVertexAttribArray(vertexAttrPosition);
    glEnableVertexAttribArray(vertexAttrNormal);
    glEnableVertexAttribArray(vertexAttrTexCoords);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(vertexAttrPosition, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position));
    glVertexAttribPointer(vertexAttrNormal, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(vertexAttrTexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void DrawableSquare::draw() const
{
    // TODO
}
