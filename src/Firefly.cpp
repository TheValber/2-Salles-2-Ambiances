// Firefly.cpp

#include "../include/Firefly.hpp"
#include <iostream>
#include "../include/vertexAttr.hpp"
#include "../include/utils.hpp"

Firefly::Firefly(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{

    _position = position;
    _rotation = rotation;
    _scale = scale;

    // Body
    insertSphereVertices(glm::vec3(0.f, 0.f, 0.f), 1.f, m_Vertices, 16, 16);
    insertSphereVertices(glm::vec3(1.f, 0.f, 0.f), 0.9f, m_Vertices, 16, 16);
    insertSphereVertices(glm::vec3(1.8f, 0.1f, 0.f), 0.7f, m_Vertices, 16, 16);
    insertCubeVertices(glm::vec3(2.1f, 0.9f, 0.3f), glm::vec3(0.1f, 0.7f, 0.1f), m_Vertices);
    insertCubeVertices(glm::vec3(2.1f, 0.9f, -0.3f), glm::vec3(0.1f, 0.7f, 0.1f), m_Vertices);

    m_nVertexCount = m_Vertices.size();

    // Wing
    insertCubeVertices(glm::vec3(0.f, 0.f, 0.f), glm::vec3(2.5f, 0.1f, 2.f), m_VerticesWings);

    m_nVertexCountWings = m_VerticesWings.size();

    // Light
    insertSphereVertices(glm::vec3(-1.f, 0.f, 0.f), 1.f, m_VerticesLight, 16, 16, true);
    insertSphereVertices(glm::vec3(-1.8f, 0.f, 0.f), 0.8f, m_VerticesLight, 16, 16, true);

    _wing1Position = glm::vec3(0.5f, 0.f, 1.5f);
    _wing2Position = glm::vec3(0.5f, 0.f, -1.5f);

    m_nVertexCountLight = m_VerticesLight.size();

    _Kd = glm::vec3(0.3f, 0.3f, 0.3f);
    _Ks = glm::vec3(0.5f, 0.5f, 0.5f);
    _Shininess = 40.f;

    _KdLight = glm::vec3(0.8f, 0.8f, 0.8f);
    _KsLight = glm::vec3(0.6f, 0.6f, 0.6f);
    _ShininessLight = 80.f;

    setMinPoint();
    setMaxPoint();
}

void Firefly::initVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_vboWings);
    glBindBuffer(GL_ARRAY_BUFFER, _vboWings);
    glBufferData(GL_ARRAY_BUFFER, m_nVertexCountWings * sizeof(ShapeVertex), m_VerticesWings.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_vboLight);
    glBindBuffer(GL_ARRAY_BUFFER, _vboLight);
    glBufferData(GL_ARRAY_BUFFER, m_nVertexCountLight * sizeof(ShapeVertex), m_VerticesLight.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Firefly::initVAO()
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

    glGenVertexArrays(1, &_vaoWings);
    glBindVertexArray(_vaoWings);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, _vboWings);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &_vaoLight);
    glBindVertexArray(_vaoLight);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, _vboLight);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Firefly::setTexture(GLuint texture)
{
    _texture = texture;
}

void Firefly::setTexture2(GLuint texture)
{
    _texture2 = texture;
}

void Firefly::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const
{
    glm::mat4 MVMat = MVMatrix * glm::translate(glm::mat4(1), _position);
    MVMat = MVMat * glm::rotate(glm::mat4(1), glm::radians(_rotation.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.y), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    MVMat = MVMat * glm::scale(glm::mat4(1), _scale);
    glm::mat4 NormalMat = glm::transpose(glm::inverse(MVMat));

    glUniform3f(uniformLocations.uKdLocation, _Kd.x, _Kd.y, _Kd.z);
    glUniform3f(uniformLocations.uKsLocation, _Ks.x, _Ks.y, _Ks.z);
    glUniform1f(uniformLocations.uShininessLocation, _Shininess);

    // Draw body
    glBindVertexArray(_vao);
    glUniformMatrix4fv(uniformLocations.uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMat));
    glUniformMatrix4fv(uniformLocations.uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMat));
    glUniformMatrix4fv(uniformLocations.uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMat));

    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(uniformLocations.uTextureLocation, 0);

    glDrawArrays(GL_TRIANGLES, 0, getVertexCount());

    glBindVertexArray(0);

    // Draw wings
    glBindVertexArray(_vaoWings);
    glm::mat4 MVMatWing1 = MVMat * glm::rotate(glm::mat4(1), glm::radians(_wingAngle), glm::vec3(1, 0, 0)) * glm::translate(glm::mat4(1), _wing1Position);
    glm::mat4 NormalMatWing1 = glm::transpose(glm::inverse(MVMatWing1));

    glUniformMatrix4fv(uniformLocations.uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatWing1));
    glUniformMatrix4fv(uniformLocations.uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatWing1));
    glUniformMatrix4fv(uniformLocations.uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatWing1));

    glDrawArrays(GL_TRIANGLES, 0, m_nVertexCountWings);

    glm::mat4 MVMatWing2 = MVMat * glm::rotate(glm::mat4(1), glm::radians(-_wingAngle), glm::vec3(1, 0, 0)) * glm::translate(glm::mat4(1), _wing2Position);
    glm::mat4 NormalMatWing2 = glm::transpose(glm::inverse(MVMatWing2));

    glUniformMatrix4fv(uniformLocations.uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatWing2));
    glUniformMatrix4fv(uniformLocations.uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatWing2));
    glUniformMatrix4fv(uniformLocations.uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatWing2));

    glDrawArrays(GL_TRIANGLES, 0, m_nVertexCountWings);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw light
    glUniformMatrix4fv(uniformLocations.uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMat));
    glUniformMatrix4fv(uniformLocations.uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMat));
    glUniformMatrix4fv(uniformLocations.uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMat));

    glBindVertexArray(_vaoLight);
    glBindTexture(GL_TEXTURE_2D, _texture2);
    glUniform1i(uniformLocations.uTextureLocation, 0);

    glDrawArrays(GL_TRIANGLES, 0, m_nVertexCountLight);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Firefly::deleteDrawable()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vboWings);
    glDeleteVertexArrays(1, &_vaoWings);
    glDeleteBuffers(1, &_vboLight);
    glDeleteVertexArrays(1, &_vaoLight);
}

glm::vec3 Firefly::getLightPosition() const
{
    glm::vec3 basePosition = glm::vec3(-1.4f, 0.f, 0.f);

    basePosition *= _scale;

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    basePosition = glm::vec3(rotationMatrix * glm::vec4(basePosition, 1.0f));

    basePosition += _position;

    return basePosition;
}

void Firefly::animate()
{
    glm::vec3 center = glm::vec3(-10.f, 1.5f, 0.f);
    float radius = 6.0f;
    float angleSpeed = 0.005f;
    static float angle = 0.0f;

    // Position
    angle += angleSpeed;
    float x = center.x + radius * cos(angle);
    float z = center.z + radius * sin(angle);
    _position = glm::vec3(x, _position.y, z);

    // Rotation
    glm::vec3 direction = glm::normalize(center - _position);
    _rotation.y = -glm::degrees(atan2(direction.z, direction.x)) + 90.0f;

    // Oscillation verticale
    _position.y = center.y + 0.5f * sin(angle * 2.0f);

    // Wing animation
    _wingAngle += _wingSpeed;
    if (_wingAngle > 30.f || _wingAngle < -30.f)
    {
        _wingSpeed *= -1;
    }
}
