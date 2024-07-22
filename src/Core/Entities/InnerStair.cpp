#include "InnerStair.hpp"

InnerStair::InnerStair(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures) : Block("BLOCK:INNER_STAIR", position, textures, INNER_STAIR_VERTICES, INNER_STAIR_INDICES, INNER_STAIR_NUMBER_OF_INDICES_PER_FACE) {}