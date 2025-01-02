// Drawable.hpp
#pragma once

#include <vector>

#include <glad/glad.h>
#include <glimac/common.hpp>

using namespace glimac;

class Drawable
{
public:
    virtual void initVBO() = 0;

    virtual void initVAO(GLuint vertexAttrPosition, GLuint vertexAttrNormal, GLuint vertexAttrTexCoords) = 0;

    virtual void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, const glm::mat4 &NormalMatrix) const = 0;

    void setLocations(GLint uMVPMatrixLocation, GLint uMVMatrixLocation, GLint uNormalMatrixLocation, GLint uTextureLocation)
    {
        this->_uMVPMatrixLocation = uMVPMatrixLocation;
        this->_uMVMatrixLocation = uMVMatrixLocation;
        this->_uNormalMatrixLocation = uNormalMatrixLocation;
        this->_uTextureLocation = uTextureLocation;
    }

    /**
     * @brief Get the pointer to the data
     *
     * @return const ShapeVertex*
     */
    const ShapeVertex *getDataPointer() const
    {
        return &m_Vertices[0];
    }

    /**
     * @brief Get the number of vertices
     *
     * @return GLsizei
     */
    GLsizei getVertexCount() const
    {
        return m_nVertexCount;
    }

protected:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount;

    GLuint _vbo;
    GLuint _vao;

    GLint _uMVPMatrixLocation;
    GLint _uMVMatrixLocation;
    GLint _uNormalMatrixLocation;
    GLint _uTextureLocation;
};
