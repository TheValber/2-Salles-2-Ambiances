// Room2.hpp
#pragma once

#include "Room.hpp"

#include "UniformLocations.hpp"

class Room2 : public Room
{
public:
    Room2(UniformLocations uniformLocations);

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix) const override;

    bool isInWall(glm::vec3 pos, float radius) const override;
};
