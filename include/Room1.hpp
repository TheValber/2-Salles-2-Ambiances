// Room1.hpp
#pragma once

#include "Room.hpp"

#include "UniformLocations.hpp"
#include "StreetLight.hpp"
#include "Firefly.hpp"

class Room1 : public Room
{
public:
    Room1();

    bool initTextures(FilePath dirPath) override;

    void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations, bool renderLights) const override;

    bool isInWall(glm::vec3 pos, float radius) const override;

    void deleteRoom() override;

    void setLightOn(bool lightOn);

    void animate();

private:
    std::vector<glm::vec3> _lightsPositions;
    std::vector<glm::vec3> _lightsColors;

    StreetLight _streetLight;
    GLuint _streetLightTexture;

    Firefly _firefly;
    GLuint _fireflyTexture;
    GLuint _fireflyTexture2;

    bool _isLightOn = true;
};
