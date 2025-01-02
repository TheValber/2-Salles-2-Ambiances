// Room.hpp
#pragma once

#include <vector>

#include "DrawableSquare.hpp"

class Room
{
public:
    virtual void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix) const = 0;

protected:
    std::vector<DrawableSquare> _floors;
    std::vector<DrawableSquare> _walls;
};
