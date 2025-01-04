// Room1.hpp
#pragma once

#include "Room.hpp"

#include "UniformLocations.hpp"

class Room1 : public Room
{
public:
    Room1();

    bool initTextures(FilePath dirPath) override;

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations, bool renderLights) const override;

    bool isInWall(glm::vec3 pos, float radius) const override;

    void deleteRoom() override;

    void setLightOn(bool lightOn);

private:
    std::vector<glm::vec3> _lightsPositions;
    std::vector<glm::vec3> _lightsColors;

    bool _isLightOn = true;
};
