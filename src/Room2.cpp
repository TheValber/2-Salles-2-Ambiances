// Room2.cpp

#include "../include/Room2.hpp"

Room2::Room2(UniformLocations uniformLocations)
{
    _floors.push_back(DrawableSquare(glm::vec3(0.5f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 4.f)));
    _floors.push_back(DrawableSquare(glm::vec3(11.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(20.f, 1.f, 24.f)));

    _walls.push_back(DrawableSquare(glm::vec3(0.5f, 2.f, 2.f), glm::vec3(-90.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 4.f)));
    _walls.push_back(DrawableSquare(glm::vec3(1.f, 2.f, 7.f), glm::vec3(0.f, 0.f, -90.f), glm::vec3(4.f, 1.f, 10.f)));
    _walls.push_back(DrawableSquare(glm::vec3(11.f, 2.f, 12.f), glm::vec3(-90.f, 0.f, 0.f), glm::vec3(20.f, 1.f, 4.f)));
    _walls.push_back(DrawableSquare(glm::vec3(21.f, 2.f, 0.f), glm::vec3(0.f, 0.f, 90.f), glm::vec3(4.f, 1.f, 24.f)));
    _walls.push_back(DrawableSquare(glm::vec3(11.f, 2.f, -12.f), glm::vec3(90.f, 0.f, 0.f), glm::vec3(20.f, 1.f, 4.f)));
    _walls.push_back(DrawableSquare(glm::vec3(1.f, 2.f, -7.f), glm::vec3(0.f, 0.f, -90.f), glm::vec3(4.f, 1.f, 10.f)));
    _walls.push_back(DrawableSquare(glm::vec3(0.5f, 2.f, -2.f), glm::vec3(90.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 4.f)));

    for (auto &floor : _floors)
    {
        floor.initVBO();
        floor.initVAO();
        floor.setLocations(uniformLocations);
    }

    for (auto &wall : _walls)
    {
        wall.initVBO();
        wall.initVAO();
        wall.setLocations(uniformLocations);
    }
}

void Room2::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix) const
{
    for (const auto &floor : _floors)
    {
        floor.draw(ProjMatrix, MVMatrix);
    }

    for (const auto &wall : _walls)
    {
        wall.draw(ProjMatrix, MVMatrix);
    }
}

bool Room2::isInWall(glm::vec3 pos, float radius) const
{
    for (const auto &wall : _walls)
    {
        if (wall.isInside(pos, radius))
        {
            return true;
        }
    }

    return false;
}
