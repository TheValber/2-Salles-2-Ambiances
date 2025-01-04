// Rock.cpp

#include "../include/Rock.hpp"
#include <iostream>
#include "../include/vertexAttr.hpp"
#include "../include/utils.hpp"

Rock::Rock(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    _position = position;
    _rotation = rotation;
    _scale = scale;

    generateRock(0.1f, 3);

    m_nVertexCount = m_Vertices.size();

    _Kd = glm::vec3(0.5f, 0.5f, 0.5f);
    _Ks = glm::vec3(0.1f, 0.1f, 0.1f);
    _Shininess = 15.f;

    setMinPoint();
    setMaxPoint();
}

void Rock::initVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rock::initVAO()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Rock::setTexture(GLuint texture)
{
    _texture = texture;
}

void Rock::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, UniformLocations uniformLocations) const
{
    glm::mat4 MVMat = MVMatrix * glm::translate(glm::mat4(1), _position);
    MVMat = MVMat * glm::rotate(glm::mat4(1), glm::radians(_rotation.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.y), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1), glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    MVMat = MVMat * glm::scale(glm::mat4(1), _scale);
    glm::mat4 NormalMat = glm::transpose(glm::inverse(MVMat));

    glUniform3f(uniformLocations.uKdLocation, _Kd.x, _Kd.y, _Kd.z);
    glUniform3f(uniformLocations.uKsLocation, _Ks.x, _Ks.y, _Ks.z);
    glUniform1f(uniformLocations.uShininessLocation, _Shininess);

    glBindVertexArray(_vao);
    glUniformMatrix4fv(uniformLocations.uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMat));
    glUniformMatrix4fv(uniformLocations.uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMat));
    glUniformMatrix4fv(uniformLocations.uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMat));

    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(uniformLocations.uTextureLocation, 0);

    glDrawArrays(GL_TRIANGLES, 0, getVertexCount());

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Rock::setMinPoint()
{
    glm::vec3 point(-1.f, -1.f, -1.f);

    point *= _scale;

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));

    point += _position;

    _minPoint = point;
}

void Rock::setMaxPoint()
{
    glm::vec3 point(1.f, 1.f, 1.f);

    point *= _scale;

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    point = glm::vec3(rotationMatrix * glm::vec4(point, 1.0f));

    point += _position;

    _maxPoint = point;
}

bool Rock::isInside(glm::vec3 pos, float radius) const
{

    if (pos.x + radius < _minPoint.x || pos.x - radius > _maxPoint.x)
    {
        return false;
    }

    if (pos.z + radius < _minPoint.z || pos.z - radius > _maxPoint.z)
    {
        return false;
    }

    return true;
}

void Rock::deleteDrawable()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}

void Rock::generateRock(float noiseStrength, int subdivisions)
{
    // Définir les sommets de base d'une boîte
    std::vector<glm::vec3> baseVertices = {
        glm::vec3(-1, -1, -1), glm::vec3(1, -1, -1),
        glm::vec3(1, -1, 1), glm::vec3(-1, -1, 1),
        glm::vec3(-1, 1, -1), glm::vec3(1, 1, -1),
        glm::vec3(1, 1, 1), glm::vec3(-1, 1, 1)};

    // Définir les indices pour former les faces initiales
    std::vector<glm::ivec3> faces = {
        {0, 1, 2}, {0, 2, 3}, // Bas
        {4, 5, 6},
        {4, 6, 7}, // Haut
        {0, 1, 5},
        {0, 5, 4}, // Face avant
        {1, 2, 6},
        {1, 6, 5}, // Droite
        {2, 3, 7},
        {2, 7, 6}, // Arrière
        {3, 0, 4},
        {3, 4, 7} // Gauche
    };

    // Ajouter bruit initial aux sommets
    for (auto &vertex : baseVertices)
    {
        vertex += glm::sphericalRand(noiseStrength);
    }

    // Subdivision des faces
    for (int i = 0; i < subdivisions; ++i)
    {
        std::vector<glm::ivec3> newFaces;
        std::map<std::pair<int, int>, int> edgeMidpoints;

        for (const auto &face : faces)
        {
            int mid0 = getMidpoint(edgeMidpoints, baseVertices, face.x, face.y);
            int mid1 = getMidpoint(edgeMidpoints, baseVertices, face.y, face.z);
            int mid2 = getMidpoint(edgeMidpoints, baseVertices, face.z, face.x);

            newFaces.push_back({face.x, mid0, mid2});
            newFaces.push_back({face.y, mid1, mid0});
            newFaces.push_back({face.z, mid2, mid1});
            newFaces.push_back({mid0, mid1, mid2});
        }

        faces = newFaces;
    }

    // Ajouter bruit final
    for (auto &vertex : baseVertices)
    {
        vertex += glm::sphericalRand(noiseStrength / 2.0f);
    }

    // Construire les sommets pour le rendu
    for (const auto &face : faces)
    {
        glm::vec3 v0 = baseVertices[face.x];
        glm::vec3 v1 = baseVertices[face.y];
        glm::vec3 v2 = baseVertices[face.z];

        glm::vec3 normal = -glm::normalize(glm::cross(v1 - v0, v2 - v0));

        m_Vertices.push_back({v0, normal, glm::vec2(0, 0)});
        m_Vertices.push_back({v1, normal, glm::vec2(1, 0)});
        m_Vertices.push_back({v2, normal, glm::vec2(0.5f, 1)});
    }
}

int Rock::getMidpoint(std::map<std::pair<int, int>, int> &edgeMidpoints,
                      std::vector<glm::vec3> &vertices,
                      int a, int b)
{
    std::pair<int, int> edge = std::minmax(a, b);
    auto it = edgeMidpoints.find(edge);
    if (it != edgeMidpoints.end())
    {
        return it->second;
    }

    glm::vec3 midpoint = (vertices[a] + vertices[b]) * 0.5f;
    midpoint += glm::sphericalRand(0.1f); // Ajout de bruit sur les arêtes
    vertices.push_back(midpoint);
    int index = vertices.size() - 1;
    edgeMidpoints[edge] = index;
    return index;
}
