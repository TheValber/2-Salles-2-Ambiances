// Cottage.hpp
#pragma once

#include <glimac/glm.hpp>

#include "Drawable.hpp"

class Cottage : public Drawable
{

public:
    Cottage(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void initVBO() override;

    void initVAO() override;

    void setTexture(GLuint texture) override;

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const override;

    bool isInside(glm::vec3 pos, float radius) const override;

    void setMinPoint() override;

    void setMaxPoint() override;

    void deleteDrawable() override;

private:
    glm::vec3 _Kd;
    glm::vec3 _Ks;
    float _Shininess;

    std::vector<glm::vec3> _minPoints;
    std::vector<glm::vec3> _maxPoints;
};
