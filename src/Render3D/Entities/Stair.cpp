#include "Stair.hpp"

namespace Render3D {

Stair::Stair(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures) : Block("BLOCK:STAIR", position, textures, STAIR_VERTICES, STAIR_INDICES, STAIR_NUMBER_OF_INDICES_PER_FACE) {}

}