// UniformLocations.hpp

#pragma once

#include <glad/glad.h>
#include <glimac/Program.hpp>

struct UniformLocations
{
    GLint uMVPMatrixLocation;
    GLint uMVMatrixLocation;
    GLint uNormalMatrixLocation;
    GLint uTextureLocation;

    UniformLocations(glimac::Program &program)
    {
        uMVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
        uMVMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
        uNormalMatrixLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
        uTextureLocation = glGetUniformLocation(program.getGLId(), "uTexture");
    }
};
