// Skybox.hpp
#pragma once

#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>

#include "Drawable.hpp"

class Skybox : public Drawable
{

public:
    Skybox(FilePath dirPath);

    void initVBO() override;

    void initVAO() override;

    void setTexture(GLuint /*texture*/) override {}

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const override;

    bool isInside(glm::vec3 /*pos*/, float /*radius*/) const override { return false; }

    void setMinPoint() override {}

    void setMaxPoint() override {}

    void deleteDrawable() override;

    void setActualTexture(int texture) { _actualTexture = texture; }

private:
    GLuint _room1Texture;
    GLuint _room2Texture;

    std::vector<glm::vec3> _vertices;

    int _actualTexture = 0;
};
