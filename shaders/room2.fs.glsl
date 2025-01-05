#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D uTexture;

uniform vec3 uAmbientLight;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

uniform vec3 uLight2Pos_vs;
uniform vec3 uLight2Intensity;

vec3 blinnPhongDir() {
    vec3 wi = normalize(uLightDir_vs);
    vec3 Li = uLightIntensity;
    vec3 w0 = normalize(-vPosition_vs);
    vec3 halfVector = normalize((wi + w0) / 2);
    return Li * (uKd * max(dot(wi, normalize(vNormal_vs)), 0) + uKs * pow(max(dot(halfVector, normalize(vNormal_vs)), 0), uShininess));
}

vec3 blinnPhongPos(vec3 lightPos, vec3 lightIntensity) {
    vec3 N = normalize(vNormal_vs);
    vec3 L = normalize(lightPos - vPosition_vs);
    vec3 V = normalize(-vPosition_vs);
    vec3 H = normalize(L + V);

    float distance = length(lightPos - vPosition_vs);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.03 * (distance * distance));

    float diffuse = max(dot(N, L), 0.0);
    float specular = pow(max(dot(N, H), 0.0), uShininess);

    return attenuation * (uKd * lightIntensity * diffuse + uKs * lightIntensity * specular);
}

vec3 cellShading(vec3 color) {
    float intensity = (color.r + color.g + color.b);
    for (float i = 1.0; i > 0.1; i -= 0.1) {
        if (intensity > i) {
            return vec3(i, i, i);
        }
    }
}

void main()
{
    vec4 color = texture(uTexture, vTexCoords);
    vec3 light = uAmbientLight + blinnPhongDir() + cellShading(blinnPhongPos(uLight2Pos_vs, uLight2Intensity));
    fFragColor = vec4(color.rgb * light, color.a);
}
