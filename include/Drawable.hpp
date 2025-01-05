// Drawable.hpp
#pragma once

#include <vector>

#include <glad/glad.h>
#include <glimac/common.hpp>

#include "UniformLocations.hpp"

using namespace glimac;

class Drawable
{
public:
    virtual ~Drawable() = default;

    virtual void initVBO() = 0;

    virtual void initVAO() = 0;

    virtual void setTexture(GLuint texture) = 0;

    virtual void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const = 0;

    virtual bool isInside(glm::vec3 pos, float radius) const = 0;

    virtual void setMinPoint() = 0;

    virtual void setMaxPoint() = 0;

    virtual void deleteDrawable() = 0;

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
    float _textureRotation;

    glm::vec3 _minPoint;
    glm::vec3 _maxPoint;

    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount;

    GLuint _vbo;
    GLuint _vao;

    GLuint _texture;
};
