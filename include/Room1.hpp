// Room1.hpp
#pragma once

#include "Room.hpp"

#include "UniformLocations.hpp"

class Room1 : public Room
{
public:
    Room1(UniformLocations uniformLocations);

    bool initTextures(FilePath dirPath) override;

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix) const override;

    bool isInWall(glm::vec3 pos, float radius) const override;

    void deleteRoom() override;
};
