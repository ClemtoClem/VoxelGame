/**
 *    ___ _            _    
 *   / __\ | ___   ___| | __
 *  /__\// |/ _ \ / __| |/ /
 * / \/  \ | (_) | (__|   < 
 * \_____/_|\___/ \___|_|\_\
 *
 * @file Block.hpp
 * @author ClemtoClem
 * @date 09/07/2024
*/

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <array>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Entity.hpp"

class Block : public Entity {
public:
	Block(const glm::vec3 &position, const std::array<std::string, 6> &textureFiles);
	virtual ~Block();

	virtual glm::vec3 &position() override;
	virtual void position(const glm::vec3 &point) override;

	virtual void update(float dt) override;
	virtual void render() const override;

private:
	void loadTextures(const std::array<std::string, 6> &textureFiles);
	void setupMesh();

	glm::vec3 _position;
	GLuint _textures[6];
	GLuint _vao, _vbo, _ebo;
};

#endif // BLOCK_HPP
