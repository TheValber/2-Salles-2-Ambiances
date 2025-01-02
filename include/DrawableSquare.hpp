// DrawableSquare.hpp
#pragma once

#include <glimac/glm.hpp>

#include "Drawable.hpp"

class DrawableSquare : public Drawable
{

public:
    DrawableSquare(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void initVBO() override;

    void initVAO() override;

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix) const override;
};
