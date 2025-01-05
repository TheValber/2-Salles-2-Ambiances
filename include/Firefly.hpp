// Firefly.hpp
#pragma once

#include <glimac/glm.hpp>

#include "Drawable.hpp"

class Firefly : public Drawable
{

public:
    Firefly(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void initVBO() override;

    void initVAO() override;

    void setTexture(GLuint texture) override;

    void setTexture2(GLuint texture);

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const override;

    bool isInside(glm::vec3 /*pos*/, float /*radius*/) const override { return false; }

    void setMinPoint() override {}

    void setMaxPoint() override {}

    void deleteDrawable() override;

    glm::vec3 getLightPosition() const;

    void animate();

private:
    glm::vec3 _Kd;
    glm::vec3 _Ks;
    float _Shininess;

    GLuint _texture2;

    std::vector<ShapeVertex> m_VerticesLight;
    GLsizei m_nVertexCountLight;
    GLuint _vboLight;
    GLuint _vaoLight;

    glm::vec3 _KdLight;
    glm::vec3 _KsLight;
    float _ShininessLight;

    std::vector<ShapeVertex> m_VerticesWings;
    GLsizei m_nVertexCountWings;
    GLuint _vboWings;
    GLuint _vaoWings;

    glm::vec3 _wing1Position;
    glm::vec3 _wing2Position;
    float _wingAngle = 0.f;
    float _wingSpeed = 1.5f;
};
