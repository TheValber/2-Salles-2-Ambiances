// Cottage.cpp

#include "../include/Cottage.hpp"
#include <iostream>
#include "../include/vertexAttr.hpp"
#include "../include/utils.hpp"

Cottage::Cottage(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{

    _position = position;
    _rotation = rotation;
    _scale = scale;

    // Murs
    insertCubeVertices(glm::vec3(4.f, 1.5f, 4.f), glm::vec3(12.f, 3.f, 0.1f), m_Vertices);
    insertCubeVertices(glm::vec3(4.f, 0.5f, -4.f), glm::vec3(12.f, 1.f, 0.1f), m_Vertices);
    insertCubeVertices(glm::vec3(4.f, 2.75f, -4.f), glm::vec3(12.f, 0.5f, 0.1f), m_Vertices);
    insertCubeVertices(glm::vec3(4.f, 1.75f, -4.f), glm::vec3(2.f, 1.5f, 0.1f), m_Vertices);
    insertCubeVertices(glm::vec3(9.f, 1.75f, -4.f), glm::vec3(2.f, 1.5f, 0.1f), m_Vertices);
    insertCubeVertices(glm::vec3(-1.f, 1.75f, -4.f), glm::vec3(2.f, 1.5f, 0.1f), m_Vertices);
    insertCubeVertices(glm::vec3(10.f, 1.5f, 0.f), glm::vec3(0.1f, 3.f, 8.f), m_Vertices);
    insertCubeVertices(glm::vec3(-2.f, 1.5f, -2.5f), glm::vec3(0.1f, 3.f, 3.f), m_Vertices);
    insertCubeVertices(glm::vec3(-2.f, 1.5f, 2.5f), glm::vec3(0.1f, 3.f, 3.f), m_Vertices);
    insertCubeVertices(glm::vec3(-2.f, 2.875f, 0.f), glm::vec3(0.1f, 0.25f, 2.f), m_Vertices);

    // Pignon
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 3.f, -4.f), glm::vec3(-1, 0, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 5.f, 0.f), glm::vec3(-1, 0, 0), glm::vec2(4, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 3.f, 4.f), glm::vec3(-1, 0, 0), glm::vec2(8, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 3.f, -4.f), glm::vec3(1, 0, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 5.f, 0.f), glm::vec3(1, 0, 0), glm::vec2(4, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 3.f, 4.f), glm::vec3(1, 0, 0), glm::vec2(8, 0)});

    m_Vertices.push_back(ShapeVertex{glm::vec3(9.95f, 3.f, -4.f), glm::vec3(-1, 0, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(9.95f, 5.f, 0.f), glm::vec3(-1, 0, 0), glm::vec2(4, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(9.95f, 3.f, 4.f), glm::vec3(-1, 0, 0), glm::vec2(8, 0)});

    // Toit
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 3.f, -4.f), glm::vec3(0, 1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 3.f, -4.f), glm::vec3(0, 1, 0), glm::vec2(12, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 5.f, 0.f), glm::vec3(0, 1, 0), glm::vec2(12, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 3.f, -4.f), glm::vec3(0, 1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 5.f, 0.f), glm::vec3(0, 1, 0), glm::vec2(12, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 5.f, 0.f), glm::vec3(0, 1, 0), glm::vec2(0, 2)});

    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 2.9f, -4.f), glm::vec3(0, -1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 2.9f, -4.f), glm::vec3(0, -1, 0), glm::vec2(12, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 4.9f, 0.f), glm::vec3(0, -1, 0), glm::vec2(12, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 2.9f, -4.f), glm::vec3(0, -1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 4.9f, 0.f), glm::vec3(0, -1, 0), glm::vec2(12, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 4.9f, 0.f), glm::vec3(0, -1, 0), glm::vec2(0, 2)});

    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 3.f, 4.f), glm::vec3(0, 1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 3.f, 4.f), glm::vec3(0, 1, 0), glm::vec2(12, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 5.f, 0.f), glm::vec3(0, 1, 0), glm::vec2(12, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 3.f, 4.f), glm::vec3(0, 1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-2.05f, 5.f, 0.f), glm::vec3(0, 1, 0), glm::vec2(12, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 5.f, 0.f), glm::vec3(0, 1, 0), glm::vec2(0, 2)});

    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 2.9f, 4.f), glm::vec3(0, -1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 2.9f, 4.f), glm::vec3(0, -1, 0), glm::vec2(12, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 4.9f, 0.f), glm::vec3(0, -1, 0), glm::vec2(12, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 2.9f, 4.f), glm::vec3(0, -1, 0), glm::vec2(0, 0)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(-1.95f, 4.9f, 0.f), glm::vec3(0, -1, 0), glm::vec2(12, 2)});
    m_Vertices.push_back(ShapeVertex{glm::vec3(10.f, 4.9f, 0.f), glm::vec3(0, -1, 0), glm::vec2(0, 2)});

    m_nVertexCount = m_Vertices.size();

    _Kd = glm::vec3(0.5f, 0.5f, 0.5f);
    _Ks = glm::vec3(0.1f, 0.1f, 0.1f);
    _Shininess = 25.f;

    setMinPoint();
    setMaxPoint();
}

void Cottage::initVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cottage::initVAO()
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

void Cottage::setTexture(GLuint texture)
{
    _texture = texture;
}

void Cottage::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const
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

void Cottage::setMinPoint()
{
    glm::vec3 point(-2.f, 4.f, -4.f);
    point *= _scale;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));
    point += _position;
    _minPoints.push_back(point);

    point = glm::vec3(-2.f, 0.f, -4.f);
    point *= _scale;
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));
    point += _position;
    _minPoints.push_back(point);

    point = glm::vec3(-2.f, 0.f, 1.5f);
    point *= _scale;
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));
    point += _position;
    _minPoints.push_back(point);
}

void Cottage::setMaxPoint()
{
    glm::vec3 point(10.f, 0.f, -4.f);
    point *= _scale;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));
    point += _position;
    _maxPoints.push_back(point);

    point = glm::vec3(-2.f, 4.f, -1.5f);
    point *= _scale;
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));
    point += _position;
    _maxPoints.push_back(point);

    point = glm::vec3(-2.f, 4.f, 4.f);
    point *= _scale;
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));
    point += _position;
    _maxPoints.push_back(point);
}

bool Cottage::isInside(glm::vec3 pos, float radius) const
{
    for (size_t i = 0; i < _minPoints.size(); i++)
    {
        glm::vec3 minPoint = _minPoints[i];
        glm::vec3 maxPoint = _maxPoints[i];

        if (pos.x + radius < minPoint.x || pos.x - radius > maxPoint.x)
        {
            continue;
        }
        if (pos.z + radius < minPoint.z || pos.z - radius > maxPoint.z)
        {
            continue;
        }

        return true;
    }

    return false;
}

void Cottage::deleteDrawable()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}
