// Room1.hpp
#pragma once

#include "Room.hpp"

#include "UniformLocations.hpp"

class Room1 : public Room
{
public:
    Room1(UniformLocations uniformLocations);

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix) const override;
};
