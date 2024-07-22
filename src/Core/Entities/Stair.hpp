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

class Stair : public Block {
public:
	Stair(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures);
};

#endif // STAIR_HPP