#include "Cube.hpp"

namespace Render3D {

Cube::Cube(const glm::vec3 &position, const std::vector<glm::vec4> facesColors)
    : Object("Object:Cube", position, facesColors, colorFaces(CUBE_VERTICES, facesColors), CUBE_INDICES, CUBE_NUMBER_OF_INDICES_PER_FACE) {}

Cube::Cube(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures)
    : Object("Object:Cube", position, textures, CUBE_VERTICES, CUBE_INDICES, CUBE_NUMBER_OF_INDICES_PER_FACE) {}

std::vector<float> Cube::colorFaces(const std::vector<float> &vertices, const std::vector<glm::vec4> &facesColors) {
    // Copiez le vecteur d'entrée pour modification
    std::vector<float> modifiedVertices = vertices;
    
    unsigned int offset = 0;
    for (unsigned int i = 0; i < CUBE_NUMBER_OF_VERTICES_PER_FACE.size(); i++) {
        for (unsigned int j = 0; j < CUBE_NUMBER_OF_VERTICES_PER_FACE[i]; j++) {
            modifiedVertices[offset + 4] = facesColors[i].r;
            modifiedVertices[offset + 5] = facesColors[i].g;
            modifiedVertices[offset + 6] = facesColors[i].b;
            modifiedVertices[offset + 7] = facesColors[i].a;
            offset += 36;
        }
    }
    return modifiedVertices;
}

}