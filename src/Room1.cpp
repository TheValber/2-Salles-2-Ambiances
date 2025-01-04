// Room1.cpp

#include "../include/Room1.hpp"

#include <glimac/Image.hpp>

Room1::Room1(UniformLocations uniformLocations)
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
        floor.setLocations(uniformLocations);
    }

    for (auto &wall : _walls)
    {
        wall.initVBO();
        wall.initVAO();
        wall.setLocations(uniformLocations);
    }
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

    return true;
}

void Room1::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix) const
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

bool Room1::isInWall(glm::vec3 pos, float radius) const
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

    glDeleteTextures(1, &_floorTexture);
    glDeleteTextures(1, &_wallTexture);

    _floors.clear();
    _walls.clear();
}
