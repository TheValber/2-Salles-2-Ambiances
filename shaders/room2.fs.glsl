#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;

uniform vec3 uAmbientLight;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
    vec3 wi = normalize(uLightDir_vs);
    vec3 Li = uLightIntensity;
    vec3 w0 = normalize(-vPosition_vs);
    vec3 halfVector = normalize((wi + w0) / 2);
    return Li * (uKd * max(dot(wi, normalize(vNormal_vs)), 0) + uKs * pow(max(dot(halfVector, normalize(vNormal_vs)), 0), uShininess));
}

void main()
{
    fFragColor = texture(uTexture, vTexCoords).rgb * (uAmbientLight + blinnPhong());
}
