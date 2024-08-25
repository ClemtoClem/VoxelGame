#include "Stair.hpp"

namespace Render3D {

Stair::Stair(const glm::vec3 &position, const std::vector<glm::vec4> facesColors)
    : Object("Object:Stair", position, facesColors, colorFaces(STAIR_VERTICES, facesColors), STAIR_INDICES, STAIR_NUMBER_OF_INDICES_PER_FACE) {}


Stair::Stair(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures)
    : Object("Object:Stair", position, textures, STAIR_VERTICES, STAIR_INDICES, STAIR_NUMBER_OF_INDICES_PER_FACE) {}

std::vector<float> Stair::colorFaces(const std::vector<float> &vertices, const std::vector<glm::vec4> &facesColors) {
    // Copiez le vecteur d'entrée pour modification
    std::vector<float> modifiedVertices = vertices;

    unsigned int offset = 0;
    for (unsigned int i = 0; i < STAIR_NUMBER_OF_VERTICES_PER_FACE.size(); i++) {
        for (unsigned int j = 0; j < STAIR_NUMBER_OF_VERTICES_PER_FACE[i]; j++) {
            // Appliquez les couleurs
            modifiedVertices[offset + 4] = facesColors[i].r;
            modifiedVertices[offset + 5] = facesColors[i].g;
            modifiedVertices[offset + 6] = facesColors[i].b;
            modifiedVertices[offset + 7] = facesColors[i].a;
            offset += 36; // Passez au prochain ensemble de vertices
        }
    }

    return modifiedVertices;
}

}