#include "Stair.hpp"

Stair::Stair(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures) : Block("BLOCK:STAIR", position, textures, STAIR_VERTICES, STAIR_INDICES) {}