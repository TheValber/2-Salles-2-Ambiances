// Rock.hpp
#pragma once

#include <glimac/glm.hpp>

#include "Drawable.hpp"
#include <map>

class Rock : public Drawable
{

public:
    Rock(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void initVBO() override;

    void initVAO() override;

    void setTexture(GLuint texture) override;

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const override;

    bool isInside(glm::vec3 pos, float radius) const override;

    void setMinPoint() override;

    void setMaxPoint() override;

    void deleteDrawable() override;

    void generateRock(float noiseStrength, int subdivisions);

    int getMidpoint(std::map<std::pair<int, int>, int> &edgeMidpoints,
                    std::vector<glm::vec3> &vertices,
                    int a, int b);

private:
    glm::vec3 _Kd;
    glm::vec3 _Ks;
    float _Shininess;
};
