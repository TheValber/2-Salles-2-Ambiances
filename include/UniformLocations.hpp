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
    GLint uPointLightsLocation;
    GLint uNumPointLightsLocation;

    GLint uAmbientLightLocation;
    GLint uKdLocation;
    GLint uKsLocation;
    GLint uShininessLocation;

    GLint uLight1Pos_vsLocation;
    GLint uLight1IntensityLocation;
    GLint uLight2Pos_vsLocation;
    GLint uLight2IntensityLocation;

    GLint uLightDir_vsLocation;
    GLint uLightIntensityLocation;

    UniformLocations(glimac::Program &program)
    {
        uMVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
        uMVMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
        uNormalMatrixLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
        uTextureLocation = glGetUniformLocation(program.getGLId(), "uTexture");

        uAmbientLightLocation = glGetUniformLocation(program.getGLId(), "uAmbientLight");
        uKdLocation = glGetUniformLocation(program.getGLId(), "uKd");
        uKsLocation = glGetUniformLocation(program.getGLId(), "uKs");
        uShininessLocation = glGetUniformLocation(program.getGLId(), "uShininess");

        uLight1Pos_vsLocation = glGetUniformLocation(program.getGLId(), "uLight1Pos_vs");
        uLight1IntensityLocation = glGetUniformLocation(program.getGLId(), "uLight1Intensity");
        uLight2Pos_vsLocation = glGetUniformLocation(program.getGLId(), "uLight2Pos_vs");
        uLight2IntensityLocation = glGetUniformLocation(program.getGLId(), "uLight2Intensity");

        uLightDir_vsLocation = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
        uLightIntensityLocation = glGetUniformLocation(program.getGLId(), "uLightIntensity");
    }
};
