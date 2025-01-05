// Room.hpp
#pragma once

#include <vector>

#include "DrawableSquare.hpp"

class Room
{
public:
    virtual ~Room() = default;

    virtual bool initTextures(FilePath dirPath) = 0;

    virtual void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations, bool renderLights) const = 0;

    virtual bool isInWall(glm::vec3 pos, float radius) const = 0;

    virtual void deleteRoom() = 0;

protected:
    std::vector<DrawableSquare> _floors;
    std::vector<DrawableSquare> _walls;

    GLuint _floorTexture;
    GLuint _wallTexture;

    glm::vec3 _ambientLight;

    glm::vec3 _floorsKd;
    glm::vec3 _floorsKs;
    float _floorsShininess;

    glm::vec3 _wallsKd;
    glm::vec3 _wallsKs;
    float _wallsShininess;
};
