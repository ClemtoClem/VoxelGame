/**
 *  __ _        _      
 * / _\ |_ __ _(_)_ __ 
 * \ \| __/ _` | | '__|
 * _\ \ || (_| | | |   
 * \__/\__\__,_|_|_|   
 * 
 * @file Stair.hpp
 * @author @ClemtoClem
 * @date 09/07/2024
 * @brief Stair class
 */

#ifndef STAIR_HPP
#define STAIR_HPP

#include "Block.hpp"

inline const std::vector<float> STAIR_VERTICES = {
	// positions          // texture coords
	// Bottom step
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	-0.25f, -0.5f, -0.5f,  1.0f, 0.0f,
	-0.25f, -0.25f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.25f, -0.5f,  0.0f, 1.0f,
	// Second step
	-0.25f, -0.5f, -0.25f,  0.0f, 0.0f,
	0.0f, -0.5f, -0.25f,  1.0f, 0.0f,
	0.0f, -0.25f, -0.25f,  1.0f, 1.0f,
	-0.25f, -0.25f, -0.25f,  0.0f, 1.0f,
	// Third step
	0.0f, -0.5f, 0.0f,  0.0f, 0.0f,
	0.25f, -0.5f, 0.0f,  1.0f, 0.0f,
	0.25f, -0.25f, 0.0f,  1.0f, 1.0f,
	0.0f, -0.25f, 0.0f,  0.0f, 1.0f,
	// Fourth step
	0.25f, -0.5f, 0.25f,  0.0f, 0.0f,
	0.5f, -0.5f, 0.25f,  1.0f, 0.0f,
	0.5f, -0.25f, 0.25f,  1.0f, 1.0f,
	0.25f, -0.25f, 0.25f,  0.0f, 1.0f,
};

inline const std::vector<unsigned int> STAIR_INDICES = {
	// Bottom step
	0, 1, 2, 2, 3, 0,
	// Second step
	4, 5, 6, 6, 7, 4,
	// Third step
	8, 9, 10, 10, 11, 8,
	// Fourth step
	12, 13, 14, 14, 15, 12,
};

class Stair : public Block {
public:
	Stair(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures);
};

#endif // STAIR_HPP