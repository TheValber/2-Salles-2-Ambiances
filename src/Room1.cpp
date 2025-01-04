// Room1.cpp

#include "../include/Room1.hpp"

#include <glimac/Image.hpp>

Room1::Room1() : _streetLight(StreetLight(glm::vec3(-10.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)))
{
    _floors.push_back(DrawableSquare(glm::vec3(-0.5f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 4.f)));
    _floors.push_back(DrawableSquare(glm::vec3(-11.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(20.f, 1.f, 24.f)));

    _walls.push_back(DrawableSquare(glm::vec3(-0.5f, 2.f, 2.f), glm::vec3(-90.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 4.f), 180.f));
    _walls.push_back(DrawableSquare(glm::vec3(-1.f, 2.f, 7.f), glm::vec3(0.f, 0.f, 90.f), glm::vec3(4.f, 1.f, 10.f), -90.f));
    _walls.push_back(DrawableSquare(glm::vec3(-11.f, 2.f, 12.f), glm::vec3(-90.f, 0.f, 0.f), glm::vec3(20.f, 1.f, 4.f), 180.f));
    _walls.push_back(DrawableSquare(glm::vec3(-21.f, 2.f, 0.f), glm::vec3(0.f, 0.f, -90.f), glm::vec3(4.f, 1.f, 24.f), 90.f));
    _walls.push_back(DrawableSquare(glm::vec3(-11.f, 2.f, -12.f), glm::vec3(90.f, 0.f, 0.f), glm::vec3(20.f, 1.f, 4.f), 0.f));
    _walls.push_back(DrawableSquare(glm::vec3(-1.f, 2.f, -7.f), glm::vec3(0.f, 0.f, 90.f), glm::vec3(4.f, 1.f, 10.f), -90.f));
    _walls.push_back(DrawableSquare(glm::vec3(-0.5f, 2.f, -2.f), glm::vec3(90.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 4.f), 0.f));

    for (auto &floor : _floors)
    {
        floor.initVBO();
        floor.initVAO();
    }

    for (auto &wall : _walls)
    {
        wall.initVBO();
        wall.initVAO();
    }

    _streetLight.initVBO();
    _streetLight.initVAO();

    _lightsPositions = {
        glm::vec3(-10.f, 3.5f, 0.f),
        glm::vec3(-4.f, 1.f, 10.f)};
    _lightsColors = {
        glm::vec3(0.9f, 0.7f, 0.5f),
        glm::vec3(0.4f, 0.8f, 0.4f)};

    _ambientLight = glm::vec3(0.02f, 0.02f, 0.06f);

    _floorsKd = glm::vec3(0.5f, 0.5f, 0.5f);
    _floorsKs = glm::vec3(0.1f, 0.1f, 0.1f);
    _floorsShininess = 15.f;

    _wallsKd = glm::vec3(0.6f, 0.6f, 0.6f);
    _wallsKs = glm::vec3(0.1f, 0.1f, 0.1f);
    _wallsShininess = 15.f;
}

bool Room1::initTextures(FilePath dirPath)
{
    auto floorImage = loadImage(dirPath + "/assets/textures/room1Floor.png");
    if (floorImage == nullptr)
    {
        return false;
    }
    glGenTextures(1, &_floorTexture);
    glBindTexture(GL_TEXTURE_2D, _floorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, floorImage->getWidth(), floorImage->getHeight(), 0, GL_RGBA, GL_FLOAT, floorImage->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    for (auto &floor : _floors)
    {
        floor.setTexture(_floorTexture);
    }

    auto wallImage = loadImage(dirPath + "/assets/textures/room1Wall.png");
    if (wallImage == nullptr)
    {
        return false;
    }
    glGenTextures(1, &_wallTexture);
    glBindTexture(GL_TEXTURE_2D, _wallTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wallImage->getWidth(), wallImage->getHeight(), 0, GL_RGBA, GL_FLOAT, wallImage->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    for (auto &wall : _walls)
    {
        wall.setTexture(_wallTexture);
    }

    auto streetLightImage = loadImage(dirPath + "/assets/textures/streetLight.png");
    if (streetLightImage == nullptr)
    {
        return false;
    }
    glGenTextures(1, &_streetLightTexture);
    glBindTexture(GL_TEXTURE_2D, _streetLightTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, streetLightImage->getWidth(), streetLightImage->getHeight(), 0, GL_RGBA, GL_FLOAT, streetLightImage->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    _streetLight.setTexture(_streetLightTexture);

    return true;
}

void Room1::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations, bool renderLights) const
{
    if (renderLights)
    {
        glm::vec3 lightPos1 = glm::vec3(MVMatrix * glm::vec4(_lightsPositions[0], 1.0));
        glUniform3f(uniformLocations.uLight1Pos_vsLocation, lightPos1.x, lightPos1.y, lightPos1.z);
        if (_isLightOn)
        {
            glUniform3f(uniformLocations.uLight1IntensityLocation, _lightsColors[0].x, _lightsColors[0].y, _lightsColors[0].z);
        }
        else
        {
            glUniform3f(uniformLocations.uLight1IntensityLocation, 0.f, 0.f, 0.f);
        }

        glm::vec3 lightPos2 = glm::vec3(MVMatrix * glm::vec4(_lightsPositions[1], 1.0));
        glUniform3f(uniformLocations.uLight2Pos_vsLocation, lightPos2.x, lightPos2.y, lightPos2.z);
        glUniform3f(uniformLocations.uLight2IntensityLocation, _lightsColors[1].x, _lightsColors[1].y, _lightsColors[1].z);

        glUniform3f(uniformLocations.uAmbientLightLocation, _ambientLight.x, _ambientLight.y, _ambientLight.z);
    }

    glUniform3f(uniformLocations.uKdLocation, _floorsKd.x, _floorsKd.y, _floorsKd.z);
    glUniform3f(uniformLocations.uKsLocation, _floorsKs.x, _floorsKs.y, _floorsKs.z);
    glUniform1f(uniformLocations.uShininessLocation, _floorsShininess);

    for (const auto &floor : _floors)
    {
        floor.draw(ProjMatrix, MVMatrix, uniformLocations);
    }

    glUniform3f(uniformLocations.uKdLocation, _wallsKd.x, _wallsKd.y, _wallsKd.z);
    glUniform3f(uniformLocations.uKsLocation, _wallsKs.x, _wallsKs.y, _wallsKs.z);
    glUniform1f(uniformLocations.uShininessLocation, _wallsShininess);

    for (const auto &wall : _walls)
    {
        wall.draw(ProjMatrix, MVMatrix, uniformLocations);
    }

    _streetLight.draw(ProjMatrix, MVMatrix, uniformLocations);
}

bool Room1::isInWall(glm::vec3 pos, float radius) const
{
    for (const auto &wall : _walls)
    {
        if (wall.isInside(pos, radius))
        {
            return true;
        }
    }

    if (_streetLight.isInside(pos, radius))
    {
        return true;
    }

    return false;
}

void Room1::deleteRoom()
{
    for (auto &floor : _floors)
    {
        floor.deleteDrawable();
    }

    for (auto &wall : _walls)
    {
        wall.deleteDrawable();
    }

    _streetLight.deleteDrawable();

    glDeleteTextures(1, &_floorTexture);
    glDeleteTextures(1, &_wallTexture);
    glDeleteTextures(1, &_streetLightTexture);

    _floors.clear();
    _walls.clear();
    _lightsPositions.clear();
    _lightsColors.clear();
}

void Room1::setLightOn(bool lightOn)
{
    _isLightOn = lightOn;
}
