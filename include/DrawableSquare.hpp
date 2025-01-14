// DrawableSquare.hpp
#pragma once

#include <glimac/glm.hpp>

#include "Drawable.hpp"

class DrawableSquare : public Drawable
{

public:
    DrawableSquare(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float textureRotation = 0);

    void initVBO() override;

    void initVAO() override;

    void setTexture(GLuint texture) override;

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const override;

    bool isInside(glm::vec3 pos, float radius) const override;

    void setMinPoint() override;

    void setMaxPoint() override;

    void deleteDrawable() override;
};
