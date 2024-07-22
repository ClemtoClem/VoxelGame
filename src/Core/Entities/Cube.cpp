#include "Cube.hpp"

Cube::Cube(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures) : Block("BLOCK:CUBE", position, textures, CUBE_VERTICES, CUBE_INDICES) {}