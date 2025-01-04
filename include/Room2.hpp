// Room2.hpp
#pragma once

#include "Room.hpp"

#include "UniformLocations.hpp"
#include "Rock.hpp"

class Room2 : public Room
{
public:
    Room2();

    bool initTextures(FilePath dirPath) override;

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations, bool renderLights) const override;

    bool isInWall(glm::vec3 pos, float radius) const override;

    void deleteRoom() override;

private:
    glm::vec3 _lightDirection;
    glm::vec3 _lightColor;

    Rock _rock1;
    Rock _rock2;
    GLuint _rockTexture;
};
