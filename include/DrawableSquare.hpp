// DrawableSquare.hpp
#pragma once

#include "Drawable.hpp"

class DrawableSquare : public Drawable
{

public:
    DrawableSquare(float width, float height, float x, float y);

    void initVBO() override;

    void initVAO(GLuint vertexAttrPosition, GLuint vertexAttrNormal, GLuint vertexAttrTexCoords) override;

    void draw() const override;

private:
    float _width;
    float _height;
    float _x;
    float _y;
};
