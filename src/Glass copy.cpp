// Glass.cpp

#include "../include/Glass.hpp"
#include <iostream>
#include "../include/vertexAttr.hpp"
#include "../include/utils.hpp"

Glass::Glass(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{

    _position = position;
    _rotation = rotation;
    _scale = scale;

    for (int i = 0; i < 5; i++)
    {
        _glassVAOs.push_back(GlassVAO());
    }

    // Base
    insertCubeVertices(glm::vec3(12.5f, 1.75f, 4.f), glm::vec3(2.99f, 1.49f, 0.1f), _glassVAOs[0].vertices);
    _drawOrder.push_back(std::make_pair(0, glm::vec3(12.5f, 1.75f, 4.f)));
    insertCubeVertices(glm::vec3(17.5f, 1.75f, 4.f), glm::vec3(2.99f, 1.49f, 0.1f), _glassVAOs[1].vertices);
    _drawOrder.push_back(std::make_pair(1, glm::vec3(17.5f, 1.75f, 4.f)));
    insertCubeVertices(glm::vec3(18.f, 1.75f, 0.f), glm::vec3(3.99f, 1.49f, 0.1f), _glassVAOs[2].vertices);
    _drawOrder.push_back(std::make_pair(2, glm::vec3(18.f, 1.75f, 0.f)));

    insertCubeVertices(glm::vec3(15.f, 1.5f, 11.f), glm::vec3(0.1f, 3.f, 2.f), _glassVAOs[3].vertices);
    _drawOrder.push_back(std::make_pair(3, glm::vec3(15.f, 1.5f, 11.f)));
    insertCubeVertices(glm::vec3(18.f, 1.5f, 11.f), glm::vec3(0.1f, 3.f, 2.f), _glassVAOs[4].vertices);
    _drawOrder.push_back(std::make_pair(4, glm::vec3(18.f, 1.5f, 11.f)));

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
    glm::vec3 cameraPos = glm::vec3(MVMatrix * glm::vec4(0, 0, 0, 1));

    std::sort(_drawOrder.begin(), _drawOrder.end(), [&cameraPos](const std::pair<int, glm::vec3> &a, const std::pair<int, glm::vec3> &b)
              { return glm::distance(cameraPos, a.second) > glm::distance(cameraPos, b.second); });

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

    for (const auto &pair : _drawOrder)
    {
        int index = pair.first;
        glBindVertexArray(_glassVAOs[index].vao);
        glDrawArrays(GL_TRIANGLES, 0, _glassVAOs[index].vertexCount);
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
