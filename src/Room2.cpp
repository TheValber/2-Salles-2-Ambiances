// Room2.cpp

#include "../include/Room2.hpp"

#include <glimac/Image.hpp>

Room2::Room2() : _rock1(Rock(glm::vec3(15.f, 0.f, -6.f), glm::vec3(20.f, 0.f, 10.f), glm::vec3(1.5f, 0.8f, 2.f))),
                 _rock2(Rock(glm::vec3(12.5f, 0.f, -7.5f), glm::vec3(10.f, 0.f, 20.f), glm::vec3(2.2f, 1.2f, 1.7f)))
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
    }

    for (auto &wall : _walls)
    {
        wall.initVBO();
        wall.initVAO();
    }

    _rock1.initVBO();
    _rock1.initVAO();

    _rock2.initVBO();
    _rock2.initVAO();

    _lightDirection = glm::vec3(-1.f, 1.f, -1.f);
    _lightColor = glm::vec3(1.f, 1.f, 1.f);

    _ambientLight = glm::vec3(0.2f, 0.2f, 0.2f);

    _floorsKd = glm::vec3(0.3f, 0.3f, 0.3f);
    _floorsKs = glm::vec3(0.1f, 0.1f, 0.1f);
    _floorsShininess = 10.f;

    _wallsKd = glm::vec3(0.4f, 0.4f, 0.4f);
    _wallsKs = glm::vec3(0.2f, 0.2f, 0.2f);
    _wallsShininess = 20.f;
}

bool Room2::initTextures(FilePath dirPath)
{
    auto floorImage = loadImage(dirPath + "/assets/textures/room2Floor.png");
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

    auto wallImage = loadImage(dirPath + "/assets/textures/room2Wall.png");
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

    auto rockImage = loadImage(dirPath + "/assets/textures/rock.png");
    if (rockImage == nullptr)
    {
        return false;
    }
    glGenTextures(1, &_rockTexture);
    glBindTexture(GL_TEXTURE_2D, _rockTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rockImage->getWidth(), rockImage->getHeight(), 0, GL_RGBA, GL_FLOAT, rockImage->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    _rock1.setTexture(_rockTexture);
    _rock2.setTexture(_rockTexture);

    return true;
}

void Room2::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations, bool renderLights) const
{
    if (renderLights)
    {
        glm::vec3 lightDir = glm::vec3(MVMatrix * glm::vec4(_lightDirection, 0.0));
        glUniform3f(uniformLocations.uLightDir_vsLocation, lightDir.x, lightDir.y, lightDir.z);
        glUniform3f(uniformLocations.uLightIntensityLocation, _lightColor.x, _lightColor.y, _lightColor.z);

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

    _rock1.draw(ProjMatrix, MVMatrix, uniformLocations);
    _rock2.draw(ProjMatrix, MVMatrix, uniformLocations);
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

    if (_rock1.isInside(pos, radius + 0.5f) || _rock2.isInside(pos, radius + 0.5f))
    {
        return true;
    }

    return false;
}

void Room2::deleteRoom()
{
    for (auto &floor : _floors)
    {
        floor.deleteDrawable();
    }

    for (auto &wall : _walls)
    {
        wall.deleteDrawable();
    }

    _rock1.deleteDrawable();
    _rock2.deleteDrawable();

    glDeleteTextures(1, &_floorTexture);
    glDeleteTextures(1, &_wallTexture);
    glDeleteTextures(1, &_rockTexture);

    _floors.clear();
    _walls.clear();
}
