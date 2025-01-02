// Drawable.hpp
#pragma once

#include <vector>

#include <glad/glad.h>
#include <glimac/common.hpp>

using namespace glimac;

class Drawable
{
public:
    virtual void draw() const = 0;

    virtual void initVBO() = 0;

    virtual void initVAO(GLuint vertexAttrPosition, GLuint vertexAttrNormal, GLuint vertexAttrTexCoords) = 0;

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
    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount;

    GLuint _vbo;
    GLuint _vao;
};
