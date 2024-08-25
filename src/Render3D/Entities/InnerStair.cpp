#include "InnerStair.hpp"

namespace Render3D {

InnerStair::InnerStair(const glm::vec3 &position, const std::vector<glm::vec4> facesColors)
    : Object("object:InnerStair", position, facesColors, colorFaces(INNER_STAIR_VERTICES, facesColors), INNER_STAIR_INDICES, INNER_STAIR_NUMBER_OF_INDICES_PER_FACE) {}

InnerStair::InnerStair(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> faceTexture)
    : Object("object:InnerStair", position, faceTexture, INNER_STAIR_VERTICES, INNER_STAIR_INDICES, INNER_STAIR_NUMBER_OF_INDICES_PER_FACE) {}

std::vector<float> InnerStair::colorFaces(const std::vector<float> &vertices, const std::vector<glm::vec4> &facesColors) {
    // Copiez le vecteur d'entrée pour modification
    std::vector<float> modifiedVertices = vertices;
    
    unsigned int offset = 0;
    for (unsigned int i = 0; i < INNER_STAIR_NUMBER_OF_VERTICES_PER_FACE.size(); i++) {
        for (unsigned int j = 0; j < INNER_STAIR_NUMBER_OF_VERTICES_PER_FACE[i]; j++) {
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