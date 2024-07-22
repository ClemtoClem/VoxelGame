/**
 *    ___      _          
 *   / __\   _| |__   ___ 
 *  / / | | | | '_ \ / _ \
 * / /__| |_| | |_) |  __/
 * \____/\__,_|_.__/ \___|
 *
 * @file Cube.hpp
 * @author @ClemtoClem
 * @date 09/07/2024
 * @brief Cube class
 */

#ifndef CUBE_HPP
#define CUBE_HPP

#include "Block.hpp"

inline const std::vector<float> CUBE_VERTICES = {
	// Points				Texture coords
	// Front face
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
	// Back face
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	// Left face
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	// Right face
	0.5f,  -0.5f, -0.5f,	0.0f, 0.0f,
	0.5f,  -0.5f,  0.5f,	1.0f, 0.0f,
	0.5f,   0.5f,  0.5f,	1.0f, 1.0f,
	0.5f,   0.5f, -0.5f,	0.0f, 1.0f,
	// Top face
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	// Bottom face
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
};

inline const std::vector<unsigned int> CUBE_INDICES = {
	// Front face
	0, 1, 2, 2, 3, 0,
	// Back face
	4, 5, 6, 6, 7, 4,
	// Left face
	8, 9, 10, 10, 11, 8,
	// Right face
	12, 13, 14, 14, 15, 12,
	// Top face
	16, 17, 18, 18, 19, 16,
	// Bottom face
	20, 21, 22, 22, 23, 20,
};

class Cube : public Block {
public:
	Cube(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures);
};

#endif // CUBE_HPP